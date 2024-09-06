use super::{id::Identifier, property_definition::PropertyDefinition};

pub struct SType {
    pub name: Identifier,
    pub id: u8,
    pub properties: Vec<PropertyDefinition>,
}

impl SType {
    pub fn new(name: Identifier, id: u8) -> Self {
        Self {
            name,
            id,
            properties: Vec::new(),
        }
    }
}

pub enum ValueTypes {
    String,
    Bool,
    F32,
    F64,
    U8,
    U16,
    U32,
    U64,
    I8,
    I16,
    I32,
    I64,
}
