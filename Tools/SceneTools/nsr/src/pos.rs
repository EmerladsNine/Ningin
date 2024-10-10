use std::fmt::{Display, Result};

#[repr(C)]
pub struct Pos {
    pub line: usize,
    pub column: usize,
}

impl Pos {
    pub fn new(line: usize, column: usize) -> Self {
        Self { line, column }
    }
}

impl Clone for Pos {
    fn clone(&self) -> Self {
        Self {
            line: self.line,
            column: self.column,
        }
    }
}
impl Copy for Pos {}

impl Display for Pos {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result {
        write!(f, "{}:{}", self.line, self.column)
    }
}
