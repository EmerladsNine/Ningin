use super::{object::Object, stype::SType};

pub struct Scene {
    pub name: Vec<u8>,
    pub types: Vec<SType>,
    pub objects: Vec<Object>,
}
impl Scene {
    pub fn new() -> Self {
        Self {
            name: Vec::new(),
            types: Vec::new(),
            objects: Vec::new(),
        }
    }
}
