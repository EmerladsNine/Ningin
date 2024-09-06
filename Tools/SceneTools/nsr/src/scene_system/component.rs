use super::{id::Identifier, property::Property};

pub struct Component {
    pub name: Identifier,
    pub properties: Vec<Property>,
}
