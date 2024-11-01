use std::{os::raw::c_void, ptr::null_mut};

use crate::pos::Pos;

#[derive(Clone)]
#[repr(C)]
#[repr(usize)]
pub enum Tokens {
    Identifier = 0,
    String = 1,
    Bool = 2,
    Lparanth = 3,
    Rparanth = 4,
    Lcb = 5,
    Rcb = 6,
    Comma = 7,
    Colon = 8,
    SemiColon = 9,
    HeadDefiner = 10,
    ChildDefiner = 11,
    TypeDefiner = 12,
    ScriptStart = 13,
    ScriptEnd = 14,
    Separator = 15,
    Plus = 16,
    Minus = 17,
    Times = 18,
    Divide = 19,
    DecimalNumber = 20,
    IntegerNumber = 21,
    Comment = 22,

    Unknown,
    EOF,

    //These Used for More Than One Char
    Number(Box<NumberData>), // arr, arr_size , is_decimal , is_signed
    IdentifierUncomplete(Box<IdentData>),
    StringUncompleted(Box<UnCompleteStringData>),
    SeparatorUncomplete(Box<SeparatorData>),
}

impl Tokens {}

pub struct Lexer {
    line: usize,
    column: usize,
    working_token: Tokens,
    is_token_ready: bool,
    is_in_comment: bool,
    pub tokens: Vec<Token>,
}

impl Lexer {
    pub fn new(size: usize) -> Self {
        Self {
            line: 1,
            column: 1,
            tokens: Vec::with_capacity(size),
            working_token: Tokens::Separator,
            is_token_ready: true,
            is_in_comment: false,
        }
    }

    pub fn lex(&mut self, input: String) {
        let mut current_index = 0;
        for captured in input.bytes() {
            if self.is_in_comment {
                if captured == b'\n' {
                    self.is_token_ready = true;
                    self.is_in_comment = false;
                    self.line += 1;
                    self.column = 1;
                }
                current_index += 1;
                continue;
            }
            
            if !self.is_token_ready {
                match &mut self.working_token {
                    Tokens::SeparatorUncomplete(data) => {
                        
                        if captured == b'\n' {
                            self.line += 1;
                            
                            data.id = 0;
                            self.column = 1;
                            self.working_token = Tokens::SeparatorUncomplete(Box::new(SeparatorData { id: data.id, line: data.line, column: data.column, start: data.start }));
                        } else if captured.is_ascii_whitespace() {
                            data.id += 1;
                            self.working_token = Tokens::SeparatorUncomplete(Box::new(SeparatorData { id: data.id, line: data.line, column: data.column, start: data.start }));
                        } else {
                            self.tokens
                                .push(Token::new(Tokens::Separator,data.start, null_mut(), Pos::new(data.line, data.column)));
                            self.column += data.id;
                            self.create_and_add(captured,current_index);
                        }
                    }

                    Tokens::Number(data) => {
                        if captured.is_ascii_digit() {
                            data.id += 1;
                            if data.id < 40 {
                                data.val[data.id] = captured;
                            } else {
                                panic!("Number Larger Than Expected {}:{}", self.line, self.column)
                            }
                            self.working_token = Tokens::Number(Box::new(NumberData { val: data.val, id: data.id, is_decimal: data.is_decimal, start: data.start }));
                        } else if captured == b'.' {
                            data.id += 1;
                            if data.id < 40 {
                                data.val[data.id] = captured;
                            } else {
                                panic!("Number Larger Than Expected {}:{}", self.line, self.column)
                            }
                            self.working_token = Tokens::Number(Box::new(NumberData { val: data.val, id: data.id, is_decimal: true, start: data.start }));
                        } else {
                            if data.is_decimal {
                                let num = std::str::from_utf8(&data.val[0..=data.id])
                                    .unwrap()
                                    .parse::<f64>()
                                    .unwrap();
                                
                                self.tokens.push(Token::new(
                                    Tokens::DecimalNumber,
                                    data.start,
                                    Box::into_raw(Box::new(num)) as *mut c_void,
                                    Pos::new(self.line, self.column),
                                ));
                            } else {
                                let num = std::str::from_utf8(&data.val[0..=data.id])
                                    .unwrap()
                                    .parse::<i128>()
                                    .unwrap();
                                self.tokens.push(Token::new(
                                    Tokens::IntegerNumber,
                                    data.start,
                                    Box::into_raw(Box::new(num)) as *mut c_void,
                                    Pos::new(self.line, self.column),
                                ));
                            }
                            self.column += data.id + 1;
                            self.create_and_add(captured,current_index);
                        }
                    }

                    Tokens::IdentifierUncomplete(data) => {
                        if captured.is_ascii_alphanumeric() || captured == b'_' {
                            data.id += 1;
                            if data.id < 200 {
                                data.val[data.id] = captured;
                            } else {
                                panic!(
                                    "Expected name maximum chars 200 at {}:{}",
                                    self.line, self.column
                                )
                            }
                            self.working_token = Tokens::IdentifierUncomplete(Box::new(IdentData { val: data.val, id: data.id, start: data.start }));
                        } else {
                            if data.val[0..=data.id] == [b'f', b'a', b'l', b's', b'e'] {
                                self.tokens.push(Token::new(
                                    Tokens::Bool,
                                    data.start,
                                    &false as *const bool as *mut c_void,
                                    Pos::new(self.line, self.column),
                                ));
                            } else if data.val[0..=data.id] == [b't', b'r', b'u', b'e'] {
                                self.tokens.push(Token::new(
                                    Tokens::Bool,
                                    data.start,
                                    &true as *const bool as *mut c_void,
                                    Pos::new(self.line, self.column),
                                ));
                            } else {
                                self.tokens.push(Token::new(
                                    Tokens::Identifier,
                                    data.start,
                                    Box::into_raw(Box::new(Identifier{name : data.val, size: data.id})) as *mut c_void,
                                    Pos::new(self.line, self.column),
                                ));
                            }
                            self.column += data.id + 1;
                            self.create_and_add(captured, current_index);
                        }
                    }

                    Tokens::Comment => {
                        if captured == b'/' {
                            self.is_in_comment = true;
                            self.tokens.push(Token::new(
                                Tokens::Comment,
                                current_index-1,
                                null_mut(),
                                Pos::new(self.line, self.column),
                            ));
                        } else {
                            self.working_token = Tokens::Divide;
                            self.tokens.push(Token::new(
                                self.working_token.clone(),
                                current_index-1,
                                null_mut(),
                                Pos::new(self.line, self.column),
                            ));
                            self.create_and_add(captured, current_index);
                        }
                    }

                    Tokens::StringUncompleted(data) => {
                        self.column += 1;
                        if data.last_is_escape_sequence {
                            if captured == b'n'{
                                data.data.push(b'\n');
                            }
                            else if captured == b'"'
                            {
                                data.data.push(b'"');
                            }
                            else if captured == b'\\'
                            {
                                data.data.push(b'\\');
                            }
                            else{} 
                            data.last_is_escape_sequence = false;    
                        } 
                        else if captured == b'"' {
                            self.tokens.push(
                                Token::new(
                                Tokens::String,
                                data.start,
                                Box::into_raw(Box::new(data.data.clone())) as *mut c_void,
                                Pos::new(self.line, self.column),
                            ));
                            self.column += 1;
                            self.is_token_ready = true;
                        }
                        else if captured == b'\\' {
                            data.last_is_escape_sequence = true;
                        }
                        else {
                            data.data.push(captured);
                        }
                    }

                    _ => {
                        panic!("If this ever happenes forgive me idk what's the problem");
                    }
                }
            } else {
                self.create_and_add(captured,current_index);
            }
            current_index += 1;
        }
        if self.is_token_ready == false {
            match &mut self.working_token {
                Tokens::SeparatorUncomplete( data) => {
                    self.tokens
                        .push(Token::new(Tokens::Separator, data.start, null_mut(), Pos::new(data.line, data.column)));
                    self.column += data.id;
                }
                Tokens::Comment => {
                    self.line += 1;
                    self.column = 1;
                }
                _ => {
                    
                }
            }
        }
        self.tokens
            .push(Token::new(Tokens::EOF,current_index, null_mut(), Pos::new(self.line, self.column)));
    }
    pub fn create_and_add(&mut self, captured: u8,start : usize) {
        self.is_token_ready = false;
        self.create(captured, start);
        if self.is_token_ready {
            self.tokens.push(Token::new(
                self.working_token.clone(),
                start,
                null_mut(),
                Pos::new(self.line, self.column),
            ));
            self.column += 1;
        }
    }
    pub fn create(&mut self, token: u8 , start : usize) {
        match token {
            b'(' => {
                self.working_token = Tokens::Lparanth;
                self.is_token_ready = true;
            }
            b')' => {
                self.working_token = Tokens::Rparanth;
                self.is_token_ready = true;
            }
            b'{' => {
                self.working_token = Tokens::Lcb;
                self.is_token_ready = true;
            }
            b'}' => {
                self.working_token = Tokens::Rcb;
                self.is_token_ready = true;
            }
            b'+' => {
                self.working_token = Tokens::Plus;
                self.is_token_ready = true;
            }
            b'-' => {
                self.working_token = Tokens::Minus;
                self.is_token_ready = true;
            }
            b'*' => {
                self.working_token = Tokens::Times;
                self.is_token_ready = true;
            }
            b'/' => self.working_token = Tokens::Comment,
            b',' => {
                self.working_token = Tokens::Comma;
                self.is_token_ready = true;
            }
            b':' => {
                self.working_token = Tokens::Colon;
                self.is_token_ready = true;
            }
            b';' => {
                self.working_token = Tokens::SemiColon;
                self.is_token_ready = true;
            }
            b'@' => {
                self.working_token = Tokens::ChildDefiner;
                self.is_token_ready = true;
            }
            b'#' => {
                self.working_token = Tokens::HeadDefiner;
                self.is_token_ready = true;
            }
            b'!' => {
                self.working_token = Tokens::TypeDefiner;
                self.is_token_ready = true;
            }
            b'<' => {
                self.working_token = Tokens::ScriptStart;
                self.is_token_ready = true;
            }
            b'>' => {
                self.working_token = Tokens::ScriptEnd;
                self.is_token_ready = true;
            }
            b'"' => self.working_token = Tokens::StringUncompleted(Box::new(UnCompleteStringData { data: Vec::new(), last_is_escape_sequence: false, start: start })),
            b'\n' => {
                self.line += 1;
                self.column = 1;
                self.working_token = Tokens::SeparatorUncomplete(Box::new(SeparatorData { id: 1, line: self.line, column: self.column, start: start }));
            }
            _ => {
                if token.is_ascii_digit() {
                    let mut ar = [0; 40];
                    ar[0] = token;
                    self.working_token = Tokens::Number(Box::new(NumberData { val: ar, id: 0, is_decimal: false, start: start }));
                }
                else if token.is_ascii_alphabetic() || token == b'_' {
                    let mut ar = [0; 200];
                    ar[0] = token;
                    self.working_token = Tokens::IdentifierUncomplete(Box::new(IdentData { val: ar, id: 0, start: start }));
                } else if token.is_ascii_whitespace() {
                    self.working_token = Tokens::SeparatorUncomplete(Box::new(SeparatorData { id: 1, line: self.line, column: self.column, start: start}));
                } else {
                    self.working_token = Tokens::Unknown;
                    self.is_token_ready = true;
                }
            }
        };
    }
}

#[repr(C)]
pub struct Token {
    pub pos: Pos,
    pub value : *mut c_void,
    pub start : usize,
    pub token: Tokens,
}

impl Token {
    pub fn new(token: Tokens, start : usize, value : *mut c_void, pos: Pos) -> Self {
        Self { token, start, value , pos }
    }
}
impl Clone for Token {
    fn clone(&self) -> Self {
        Self {
            pos: self.pos,
            start: self.start,
            value: self.value,
            token: self.token.clone(),
        }
    }
}

#[repr(C)]
pub struct Identifier{
    pub name : [u8;200],
    pub size : usize
}

#[derive(Clone)]
#[repr(C)]
pub struct NumberData {
    pub val: [u8; 40],
    pub id: usize,
    pub is_decimal: bool,
    pub start: usize,
}

#[derive(Clone)]
#[repr(C)]
pub struct IdentData {
    pub val: [u8; 200],
    pub id: usize,
    pub start: usize,
}

#[derive(Clone)]
#[repr(C)]
pub struct UnCompleteStringData {
    pub data: Vec<u8>,
    pub last_is_escape_sequence: bool,
    pub start: usize,
}

#[derive(Clone)]
#[repr(C)]
pub struct SeparatorData {
    pub id: usize,
    pub line: usize,
    pub column: usize,
    pub start: usize,
}