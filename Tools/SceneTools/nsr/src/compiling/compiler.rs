use std::{fs, io};

use crate::{
    lexer::{Lexer, Tokens},
    parser::parser::Parser,
    scene_system::{
        object::Object,
        scene::Scene,
        stype::{SType, ValueTypes},
    },
};

const VERSION: f32 = 1.0;
pub struct Compiler {
    types: Vec<SType>,
    file: Vec<u8>,
    strings: Vec<Vec<u8>>,
    string_section: Vec<u8>,
    obj_section: Vec<u8>,
    components_section: Vec<u8>,
    properties_section: Vec<u8>,
    id_state: u32,
}
impl Compiler {
    pub fn new(types: Vec<SType>) -> Self {
        Self {
            file: Vec::new(),
            strings: Vec::new(),
            string_section: Vec::new(),
            obj_section: Vec::new(),
            components_section: Vec::new(),
            properties_section: Vec::new(),
            types,
            id_state: 0,
        }
    }

    pub fn from(path: &str) -> Self {
        let file = fs::read_to_string(path).unwrap();
        let mut lexer = Lexer::new(file.len());
        lexer.lex(file);
        let mut parser = Parser::new(lexer.tokens, 0);
        parser.parse();
        Compiler::new(parser.scene.types)
    }

    pub fn write_to(&self, path: &str) -> io::Result<()> {
        fs::write(path, &self.file)
    }

    pub fn compile(&mut self, scene: &mut Scene) {
        scene.name.push(b'\0');
        self.strings.push(scene.name.clone());
        self.string_section.extend(scene.name.clone());

        for obj in scene.objects.iter_mut() {
            self.compile_object(obj, 0);
        }
        self.compile_header();
    }

    pub fn compile_header(&mut self) {
        //Magic Word
        self.file.extend([b'N', b'G', b'I', b'N']);
        //Version
        self.file.extend(VERSION.to_be_bytes());
        let mut data = Vec::new();

        //header
        data.extend(32_u32.to_be_bytes());
        data.extend((self.obj_section.len() as u32).to_be_bytes());
        data.extend((self.components_section.len() as u32).to_be_bytes());
        data.extend((self.properties_section.len() as u32).to_be_bytes());
        data.extend((self.string_section.len() as u32).to_be_bytes());

        //data
        data.extend(&self.obj_section);
        data.extend(&self.components_section);
        data.extend(&self.properties_section);
        data.extend(&self.string_section);
        let checksum = self.checksum(&data);
        self.file.extend(checksum);
        self.file.extend(data);
    }
    pub fn checksum(&mut self, data: &Vec<u8>) -> [u8; 4] {
        const MOD_ADLER: u32 = 65521;
        let len = data.len();
        let mut a: u32 = 1;
        let mut b: u32 = 0;
        let mut index = 0;
        while index < len {
            a = (a + data.get(index).unwrap().clone() as u32) % MOD_ADLER;
            b = (b + a) % MOD_ADLER;
            index += 1;
        }
        let r = (b << 16) | a;
        r.to_be_bytes()
    }

    pub fn compile_object(&mut self, obj: &Object, parent_id: u32) {
        let mut text = obj.name.to_vec();
        text.push(b'\0');
        let object_name_pointer = if let Some(i) = self.strings.iter().position(|ar| *ar == text) {
            (i as u32).to_be_bytes()
        } else {
            let i = self.strings.len();
            self.strings.push(text.clone());
            self.string_section.extend(text);
            (i as u32).to_be_bytes()
        };

        self.id_state += 1;
        let obj_id = self.id_state;
        self.obj_section.extend(self.id_state.to_be_bytes());
        self.obj_section.extend(object_name_pointer);
        self.obj_section.extend(parent_id.to_be_bytes());

        self.obj_section
            .extend((obj.components.len() as u16).to_be_bytes());
        obj.components.iter().for_each(|comp| {
            if let Some(typ) = self.types.iter_mut().find(|typ| typ.name == comp.name) {
                self.obj_section
                    .extend((self.components_section.len() as u32).to_be_bytes());
                self.components_section.extend(typ.id.to_be_bytes());
                self.components_section
                    .extend((comp.properties.len() as u16).to_be_bytes());
                for prop in comp.properties.iter() {
                    self.components_section
                        .extend((self.properties_section.len() as u32).to_be_bytes());
                    if let Some(propdef) = typ.properties.iter().find(|p| p.name == prop.name) {
                        let mut text = prop.name.to_vec();
                        text.push(b'\0');
                        if let Some(i) = self.strings.iter().position(|ar| *ar == text) {
                            self.properties_section.extend((i as u32).to_be_bytes());
                        } else {
                            let i = self.strings.len();
                            self.strings.push(text.clone());
                            self.string_section.extend(text);
                            self.properties_section.extend((i as u32).to_be_bytes());
                        }

                        if propdef.values.len() != prop.values.len() {
                            panic!(
                                "Expected {} Arguments , Found {} ",
                                propdef.values.len(),
                                prop.values.len()
                            );
                        }

                        let mut prop_iter = prop.values.iter();
                        for def in propdef.values.iter() {
                            match def {
                                ValueTypes::Bool => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::Bool => {
                                                let bool_ptr = val.value as *const bool;

                                                let bool_value= unsafe { *bool_ptr };

                                                let bytes: u8 = bool_value as u8;

                                                self.properties_section.extend(bytes.to_be_bytes());
                                            }
                                            _ => {
                                                panic!("Expected a Bool at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::I64 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match i64::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected I64 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected I64 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::U64 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match u64::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected U64 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected U64 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::I32 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match i32::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected I32 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected I32 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::U32 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match u32::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected U32 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected U32 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::I16 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match i16::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected I16 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected I16 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::U16 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match u16::try_from(num) {
                                                    Ok(i) => {
                                                        self.properties_section
                                                            .extend(i.to_be_bytes());
                                                    }
                                                    Err(_) => {
                                                        panic!("Expected U16 at {}", val.pos);
                                                    }
                                                }
                                            }
                                            _ => {
                                                panic!("Expected U16 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::I8 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => 
                                        {
                                            let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                            match i8::try_from(num) {
                                                Ok(i) => {
                                                    self.properties_section.extend(i.to_be_bytes());
                                                }
                                                Err(_) => {
                                                    panic!("Expected I8 at {}", val.pos);
                                                }
                                            }
                                        },
                                            _ => {
                                                panic!("Expected I8 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::U8 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::IntegerNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                match u8::try_from(num) {
                                                Ok(i) => {
                                                    self.properties_section.extend(i.to_be_bytes());
                                                }
                                                Err(_) => {
                                                    panic!("Expected U8 at {}", val.pos);
                                                }
                                               }
                                            },
                                            _ => {
                                                panic!("Expected U8 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::F32 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::DecimalNumber => {
                                                let num_ptr = val.value as *mut f64;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                self.properties_section
                                                    .extend((num as f32).to_be_bytes());
                                            }
                                            _ => {
                                                panic!("Expected F32 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::F64 => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::DecimalNumber => {
                                                let num_ptr = val.value as *mut i128;
                                                let num = unsafe {
                                                    *num_ptr
                                                };
                                                self.properties_section.extend(num.to_be_bytes());
                                            }
                                            _ => {
                                                panic!("Expected F64 at {} ", val.pos)
                                            }
                                        }
                                    }
                                }

                                ValueTypes::String => {
                                    if let Some(val) = prop_iter.next() {
                                        match val.token.clone() {
                                            Tokens::String => {
                                                let i = self.strings.len();
                                                let val_ptr = val.value as *mut Vec<u8>;
                                                let v = unsafe {
                                                    &mut *val_ptr
                                                };
                                                let mut property_value = v.clone();
                                                property_value.push(b'\0');
                                                self.strings.push(property_value.clone());
                                                self.string_section.extend(property_value);
                                                self.properties_section
                                                    .extend((i as u32).to_be_bytes());
                                            }
                                            _ => {
                                                panic!("Expected a String at {} ", val.pos)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        panic!("Property '{}', does not exist ", prop.name.to_string())
                    }
                }
            } else {
                panic!("Type '{}', does not exit", comp.name.to_string());
            }
        });

        self.obj_section
            .extend((obj.scripts.len() as u16).to_be_bytes());
        for script in obj.scripts.iter() {
            let mut text = script.clone();
            text.push(b'\0');
            if let Some(i) = self.strings.iter().position(|ar| *ar == text) {
                self.obj_section.extend((i as u32).to_be_bytes());
            } else {
                let i = self.strings.len();
                self.strings.push(text.clone());
                self.string_section.extend(text);
                self.obj_section.extend((i as u32).to_be_bytes());
            }
        }

        for obj in obj.children.iter() {
            self.compile_object(obj, obj_id);
        }
    }
}
