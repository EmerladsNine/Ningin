pub struct Identifier {
    id: [u8; 200],
    size: usize,
}
impl Identifier {
    pub fn new(id: [u8; 200], size: usize) -> Self {
        Self { id, size }
    }
    pub fn to_string(&self) -> String {
        std::str::from_utf8(&self.id[0..self.size + 1])
            .unwrap()
            .to_string()
    }
    pub fn to_vec(&self) -> Vec<u8> {
        self.id[0..self.size + 1].to_vec()
    }
}

impl PartialEq for Identifier {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}
