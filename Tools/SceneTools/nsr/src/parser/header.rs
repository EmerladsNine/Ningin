use crate::{
    lexer::Tokens,
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
                    Tokens::String(name) => {
                        self.scene.name = name;
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
            Tokens::Identifier(name, id) => {
                return Property::new(Identifier::new(name, id), self.read_values());
            }
            _ => {
                panic!("Expected an Identifier at {}", token.pos);
            }
        }
    }
}
