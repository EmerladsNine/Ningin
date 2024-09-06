use crate::{
    lexer::{Token, Tokens},
    scene_system::{
        component::Component,
        id::Identifier,
        object::Object,
        property::Property,
        property_definition::PropertyDefinition,
        scene::Scene,
        stype::{SType, ValueTypes},
    },
};

pub struct Parser {
    pub tokens: Vec<Token>,
    pub pos: usize,
    pub scene: Scene,
}

impl Parser {
    pub fn new(tokens: Vec<Token>, pos: usize) -> Self {
        Self {
            tokens,
            pos,
            scene: Scene::new(),
        }
    }

    pub fn peek(&self) -> Option<&Token> {
        self.tokens.get(self.pos)
    }

    pub fn advance(&mut self) -> Option<&Token> {
        let tok = self.tokens.get(self.pos);
        self.pos += 1;
        return tok;
    }

    pub fn parse(&mut self) {
        while let Some(token) = self.advance() {
            match token.token {
                Tokens::HeadDefiner => {
                    let prop = self.get_head_property();
                    self.use_head_property(prop);
                }

                Tokens::ChildDefiner => {
                    let obj = self.get_object();
                    self.scene.objects.push(obj);
                }

                Tokens::TypeDefiner => {
                    let typ = self.get_type();
                    self.scene.types.push(typ);
                }

                Tokens::Separator => {}

                Tokens::EOF => {
                    break;
                }

                _ => {
                    panic!("Unexpected character at {}", token.pos)
                }
            }
        }
    }
    pub fn get_type(&mut self) -> SType {
        let name = self.read_id();
        let mut token = self.advance().unwrap().clone();
        let id: u32 = match token.token {
            Tokens::Colon => {
                token = self.advance().unwrap().clone();
                match token.token {
                    Tokens::IntegerNumber(num) => match num.try_into() {
                        Ok(i) => i,
                        Err(_) => {
                            panic!("Expected U32 Id at {}", token.pos);
                        }
                    },
                    _ => {
                        panic!("Expected U32 Id at {}", token.pos);
                    }
                }
            }
            _ => {
                panic!("Expected a colon at {}", token.pos)
            }
        };
        let mut typ = SType::new(Identifier::new(name.0, name.1), id as u8);

        let token = self.peek().unwrap().clone();
        if !self.opened_curly() {
            panic!(
                "A Type Should Have a Body {} , consider using curly braces",
                token.pos
            );
        }

        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::Identifier(name, size) => {
                    self.pos += 1;
                    typ.properties.push(PropertyDefinition::new(
                        Identifier::new(name, size),
                        self.read_signature(),
                    ));
                }

                Tokens::ChildDefiner => {
                    panic!("A type can't have children {}", token.pos);
                }

                Tokens::Separator => {
                    self.pos += 1;
                }
                _ => {
                    break;
                }
            }
        }
        self.closed_curly();
        typ
    }

    pub fn get_object(&mut self) -> Object {
        let mut obj = Object::new(
            Identifier::new([0; 200], 0),
            Vec::new(),
            Vec::new(),
            Vec::new(),
        );
        let id = self.read_id();
        obj.name = Identifier::new(id.0, id.1);

        if !self.opened_curly() {
            return obj;
        }

        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::Identifier(_, _) => {
                    let result = self.read_component();
                    if obj.components.iter().any(|comp| comp.name == result.name) {
                        panic!(
                            "Component '{}' already exists {}",
                            result.name.to_string(),
                            token.pos
                        );
                    }
                    obj.components.push(result);
                }

                Tokens::ScriptStart => {
                    self.pos += 1;
                    obj.scripts.extend(self.read_scripts());
                }

                Tokens::ChildDefiner => {
                    self.pos += 1;
                    let result = self.get_object();
                    if self
                        .scene
                        .objects
                        .iter()
                        .any(|object| object.name == result.name)
                    {
                        panic!(
                            "An object with the same name already exists {}",
                            result.name.to_string()
                        )
                    }
                    obj.children.push(result);
                }
                Tokens::Separator => {
                    self.pos += 1;
                }
                _ => {
                    break;
                }
            }
        }
        self.closed_curly();
        obj
    }
    pub fn read_component(&mut self) -> Component {
        let (id, size) = self.read_id();

        let mut comp = Component {
            name: Identifier::new(id, size),
            properties: Vec::new(),
        };

        if !self.opened_curly() {
            return comp;
        }

        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::Identifier(val, id) => {
                    self.pos += 1;
                    comp.properties
                        .push(Property::new(Identifier::new(val, id), self.read_values()));
                }

                Tokens::ScriptStart => {
                    panic!("A component can't have a script , error at {}", token.pos)
                }

                Tokens::ChildDefiner => {
                    panic!("A component can't have a child , error at {}", token.pos)
                }
                Tokens::Separator => {
                    self.pos += 1;
                }
                _ => {
                    break;
                }
            }
        }

        self.closed_curly();
        comp
    }

    pub fn read_scripts(&mut self) -> Vec<Vec<u8>> {
        let mut scripts = Vec::new();
        let token = self.peek().unwrap().clone();
        let mut script = Vec::new();
        match token.token {
            Tokens::Identifier(val, id) => {
                self.pos += 1;
                script = val[0..=id].to_vec();
                script.push(b'.');
            }
            _ => {}
        }

        let mut comma_in_use = true;
        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::String(val) => {
                    if comma_in_use {
                        self.pos += 1;
                        let mut script = script.clone();
                        script.extend(val);
                        scripts.push(script);
                        comma_in_use = false;
                    } else {
                        panic!("Expected COMMA at {}", token.pos);
                    }
                }

                Tokens::Comma => {
                    self.pos += 1;
                    if !comma_in_use {
                        comma_in_use = true;
                    } else {
                        panic!("Expected a value at {}", token.pos)
                    }
                }

                Tokens::Separator => {
                    self.pos += 1;
                }

                Tokens::ScriptEnd => {
                    self.pos += 1;
                    break;
                }

                _ => {
                    panic!("Expected a string at {}", token.pos);
                }
            }
        }
        scripts
    }

    pub fn read_signature(&mut self) -> Vec<ValueTypes> {
        let mut vals: Vec<ValueTypes> = Vec::new();
        let mut comma_in_use = true;
        self.opened_parenthesis();
        loop {
            let token = self.peek().unwrap().clone();
            match &token.token {
                Tokens::Identifier(val, id) => {
                    if comma_in_use {
                        self.pos += 1;
                        let val = std::str::from_utf8(&val[0..=*id]).unwrap();
                        if val == "Double" || val == "F64" {
                            vals.push(ValueTypes::F64);
                        } else if val == "Float" || val == "F32" {
                            vals.push(ValueTypes::F32);
                        } else if val == "Long" || val == "I64" {
                            vals.push(ValueTypes::I64);
                        } else if val == "Int" || val == "I32" {
                            vals.push(ValueTypes::I32);
                        } else if val == "Short" || val == "I16" {
                            vals.push(ValueTypes::I16);
                        } else if val == "Byte" || val == "I8" {
                            vals.push(ValueTypes::I8);
                        } else if val == "I8" {
                            vals.push(ValueTypes::I8);
                        } else if val == "U64" {
                            vals.push(ValueTypes::U64);
                        } else if val == "U32" {
                            vals.push(ValueTypes::U32);
                        } else if val == "U16" {
                            vals.push(ValueTypes::U16);
                        } else if val == "U8" {
                            vals.push(ValueTypes::U8);
                        } else if val == "String" {
                            vals.push(ValueTypes::String);
                        } else if val == "Bool" {
                            vals.push(ValueTypes::Bool);
                        } else {
                            panic!("Invalid value type at {}", token.pos)
                        }

                        comma_in_use = false;
                    } else {
                        panic!("Expected COMMA at {}", token.pos);
                    }
                }

                Tokens::Comma => {
                    self.pos += 1;
                    if !comma_in_use {
                        comma_in_use = true;
                    } else {
                        panic!("Expected a value at {}", token.pos)
                    }
                }

                Tokens::Separator => {
                    self.pos += 1;
                }

                _ => {
                    break;
                }
            }
        }
        self.closed_parenthesis();
        vals
    }

    pub fn read_values(&mut self) -> Vec<Token> {
        let mut vals: Vec<Token> = Vec::new();
        let mut comma_in_use = true;
        self.opened_parenthesis();
        loop {
            let token = self.peek().unwrap().clone();
            match &token.token {
                Tokens::Bool(_) => {
                    if comma_in_use {
                        self.pos += 1;
                        vals.push(token);
                        comma_in_use = false;
                    } else {
                        panic!("Expected COMMA at {}", token.pos);
                    }
                }

                Tokens::Plus
                | Tokens::Minus
                | Tokens::DecimalNumber(..)
                | Tokens::IntegerNumber(..) => {
                    if comma_in_use {
                        vals.push(self.parse_expression());
                        comma_in_use = false;
                    } else {
                        panic!("Expected COMMA at {}", token.pos);
                    }
                }

                Tokens::String(_) => {
                    if comma_in_use {
                        self.pos += 1;
                        vals.push(token);
                        comma_in_use = false;
                    } else {
                        panic!("Expected COMMA at {}", token.pos);
                    }
                }

                Tokens::Comma => {
                    self.pos += 1;
                    if !comma_in_use {
                        comma_in_use = true;
                    } else {
                        panic!("Expected a value at {}", token.pos)
                    }
                }

                Tokens::Separator => {
                    self.pos += 1;
                }

                _ => {
                    break;
                }
            }
        }
        self.closed_parenthesis();
        vals
    }

    pub fn read_id(&mut self) -> ([u8; 200], usize) {
        let token = self.advance().unwrap().clone();
        match token.token {
            Tokens::Identifier(name, id) => {
                return (name, id);
            }
            _ => {
                panic!("Expected an Identifier at {}", token.pos);
            }
        };
    }

    pub fn opened_curly(&mut self) -> bool {
        let firsttoken = self.peek().unwrap().clone();
        loop {
            let token = self.advance().unwrap().clone();
            match token.token {
                Tokens::Lcb => {
                    return true;
                }
                Tokens::SemiColon => {
                    return false;
                }
                Tokens::Separator => {}
                _ => {
                    panic!("Expected opened curly braces at {}", firsttoken.pos);
                }
            }
        }
    }

    pub fn closed_curly(&mut self) {
        let firsttoken = self.peek().unwrap().clone();
        loop {
            let token = self.advance().unwrap().clone();
            match token.token {
                Tokens::Rcb => {
                    break;
                }
                Tokens::Separator => {}
                _ => {
                    panic!("Expected closed curly braces at {}", firsttoken.pos);
                }
            }
        }
    }
    pub fn opened_parenthesis(&mut self) {
        let firsttoken = self.peek().unwrap().clone();
        loop {
            let token = self.advance().unwrap().clone();
            match token.token {
                Tokens::Lparanth => {
                    break;
                }
                Tokens::Separator => {}
                _ => {
                    panic!("Expected opening parenthesis at {}", firsttoken.pos);
                }
            }
        }
    }

    pub fn closed_parenthesis(&mut self) {
        let firsttoken = self.peek().unwrap().clone();
        loop {
            let token = self.advance().unwrap().clone();
            match token.token {
                Tokens::Rparanth => {
                    break;
                }
                Tokens::Separator => {}
                Tokens::Identifier(val, _) => {
                    panic!(
                        "Expected a valid value not '{}' at {}",
                        std::str::from_utf8(&val).unwrap(),
                        token.pos
                    );
                }
                _ => {
                    panic!("Expected closing parenthesis at {}", firsttoken.pos);
                }
            }
        }
    }
}
