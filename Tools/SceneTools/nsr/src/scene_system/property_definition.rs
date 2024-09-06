use super::{id::Identifier, stype::ValueTypes};

pub struct PropertyDefinition {
    pub name: Identifier,
    pub values: Vec<ValueTypes>,
}

impl PropertyDefinition {
    pub fn new(name: Identifier, values: Vec<ValueTypes>) -> Self {
        Self { name, values }
    }
}
