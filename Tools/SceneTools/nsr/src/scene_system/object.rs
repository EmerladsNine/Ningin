use super::{component::Component, id::Identifier};

pub struct Object {
    pub name: Identifier,
    pub components: Vec<Component>,
    pub scripts: Vec<Vec<u8>>,
    pub children: Vec<Object>,
}

impl Object {
    pub fn new(
        name: Identifier,
        components: Vec<Component>,
        scripts: Vec<Vec<u8>>,
        children: Vec<Object>,
    ) -> Self {
        Self {
            name,
            components,
            scripts,
            children,
        }
    }
}
