use crate::lexer::Token;

use super::id::Identifier;

pub struct Property {
    pub name: Identifier,
    pub values: Vec<Token>,
}

impl Property {
    pub fn new(name: Identifier, values: Vec<Token>) -> Self {
        Self { name, values }
    }
}
