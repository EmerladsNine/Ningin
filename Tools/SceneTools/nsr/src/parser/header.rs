use crate::{
    lexer::{self, Tokens},
    parser::parser::Parser,
    scene_system::{id::Identifier, property::Property},
};

impl Parser {
    pub fn use_head_property(&mut self, prop: Property) {
        let name = prop.name.to_string();
        match name.as_str() {
            "Title" => {
                if prop.values.len() != 1 {
                    panic!(
                        "Property '{}' Takes 1 Argument , Found {}",
                        name,
                        prop.values.len()
                    )
                }
                let val = prop.values[0].clone();
                match val.token {
                    Tokens::String => {
                        let val_ptr = val.value as *mut Vec<u8>;
                        let name = unsafe {
                           &mut *val_ptr
                        };
                        self.scene.name = name.clone();
                    }
                    _ => {
                        panic!("Wrong Argument given, expected String at {}", val.pos)
                    }
                }
            }
            _ => {
                panic!("Property {} Doesn't Exist", name)
            }
        }
    }

    pub fn get_head_property(&mut self) -> Property {
        let token = self.advance().unwrap().clone();
        match token.token {
            Tokens::Identifier => {
                let identifier_ptr = token.value as *mut lexer::Identifier ;
                let identifier = unsafe {
                    &mut *identifier_ptr
                };
                return Property::new(Identifier::new(identifier.name, identifier.size), self.read_values());
            }
            _ => {
                panic!("Expected an Identifier at {}", token.pos);
            }
        }
    }
}
