use crate::pos::Pos;

#[derive(Clone)]
pub enum Tokens {
    Identifier([u8; 200], usize),
    String(Vec<u8>),
    Bool(bool),
    Lparanth,
    Rparanth,
    Lcb,
    Rcb,
    Comma,
    Colon,
    SemiColon,
    HeadDefiner,
    ChildDefiner,
    TypeDefiner,
    ScriptStart,
    ScriptEnd,
    Separator,
    Plus,
    Minus,
    Times,
    Divide,

    Unknown,
    EOF,

    //These Used for More Than One Char
    Number([u8; 40], usize, bool), // arr, arr_size , is_decimal , is_signed
    DecimalNumber(f64),
    IntegerNumber(i128),
    IdentifierUncomplete([u8; 200], usize),
    StringUncompleted(Vec<u8>,bool),
    SeparatorUncomplete(usize, usize, usize),
    Comment,
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
        for captured in input.bytes() {
            if self.is_in_comment {
                if captured == b'\n' {
                    self.is_token_ready = true;
                    self.is_in_comment = false;
                    self.line += 1;
                    self.column = 1;
                }
                continue;
            }

            if !self.is_token_ready {
                match &mut self.working_token {
                    Tokens::SeparatorUncomplete(mut id, line, column) => {
                        if captured == b'\n' {
                            self.line += 1;
                            id = 0;
                            self.column = 1;
                            self.working_token = Tokens::SeparatorUncomplete(id, *line, *column);
                        } else if captured.is_ascii_whitespace() {
                            id += 1;
                            self.working_token = Tokens::SeparatorUncomplete(id, *line, *column);
                        } else {
                            self.tokens
                                .push(Token::new(Tokens::Separator, Pos::new(*line, *column)));
                            self.column += id;
                            self.create_and_add(captured);
                        }
                    }

                    Tokens::Number(mut v, mut id, is_decimal) => {
                        if captured.is_ascii_digit() {
                            id += 1;
                            if id < 40 {
                                v[id] = captured;
                            } else {
                                panic!("Number Larger Than Expected {}:{}", self.line, self.column)
                            }
                            self.working_token = Tokens::Number(v, id, *is_decimal);
                        } else if captured == b'.' {
                            id += 1;
                            if id < 40 {
                                v[id] = captured;
                            } else {
                                panic!("Number Larger Than Expected {}:{}", self.line, self.column)
                            }
                            self.working_token = Tokens::Number(v, id, true);
                        } else {
                            if *is_decimal {
                                let num = std::str::from_utf8(&v[0..=id])
                                    .unwrap()
                                    .parse::<f64>()
                                    .unwrap();
                                self.working_token = Tokens::DecimalNumber(num);
                            } else {
                                let num = std::str::from_utf8(&v[0..=id])
                                    .unwrap()
                                    .parse::<i128>()
                                    .unwrap();
                                self.working_token = Tokens::IntegerNumber(num);
                            }
                            self.tokens.push(Token::new(
                                self.working_token.clone(),
                                Pos::new(self.line, self.column),
                            ));
                            self.column += id + 1;
                            self.create_and_add(captured);
                        }
                    }

                    Tokens::IdentifierUncomplete(mut v, mut id) => {
                        if captured.is_ascii_alphanumeric() || captured == b'_' {
                            id += 1;
                            if id < 200 {
                                v[id] = captured;
                            } else {
                                panic!(
                                    "Expected name maximum chars 200 at {}:{}",
                                    self.line, self.column
                                )
                            }
                            self.working_token = Tokens::IdentifierUncomplete(v, id);
                        } else {
                            if v[0..=id] == [b'f', b'a', b'l', b's', b'e'] {
                                self.tokens.push(Token::new(
                                    Tokens::Bool(false),
                                    Pos::new(self.line, self.column),
                                ));
                            } else if v[0..=id] == [b't', b'r', b'u', b'e'] {
                                self.tokens.push(Token::new(
                                    Tokens::Bool(true),
                                    Pos::new(self.line, self.column),
                                ));
                            } else {
                                self.tokens.push(Token::new(
                                    Tokens::Identifier(v, id),
                                    Pos::new(self.line, self.column),
                                ));
                            }
                            self.column += id + 1;
                            self.create_and_add(captured);
                        }
                    }

                    Tokens::Comment => {
                        if captured == b'/' {
                            self.is_in_comment = true;
                        } else {
                            self.working_token = Tokens::Divide;
                            self.tokens.push(Token::new(
                                self.working_token.clone(),
                                Pos::new(self.line, self.column),
                            ));
                            self.create_and_add(captured);
                        }
                    }

                    Tokens::StringUncompleted(s,last_is_escape_sequence) => {
                        self.column += 1;
                        if *last_is_escape_sequence {
                            if captured == b'n'{
                                s.push(b'\n');
                            }
                            else if captured == b'\\'
                            {
                                s.push(b'\\');
                            }
                            else{
                                panic!(
                                    "Expected an escape character at {} ",
                                    Pos::new(self.line, self.column)
                                )
                            } 
                            *last_is_escape_sequence = false;    
                        } 
                        else if captured == b'"' {
                            self.tokens.push(
                                Token::new(
                                Tokens::String(s.clone()),
                                Pos::new(self.line, self.column),
                            ));
                            self.column += 1;
                            self.is_token_ready = true;
                        } else if captured == b'\n' {
                            panic!(
                                "Expected a second \" at {} ",
                                Pos::new(self.line, self.column)
                            )
                        }
                        else if captured == b'\\' {
                            *last_is_escape_sequence = true;
                        }
                        else {
                            s.push(captured);
                        }
                    }

                    _ => {
                        panic!("If this ever happenes forgive me idk what's the problem");
                    }
                }
            } else {
                self.create_and_add(captured);
            }
        }
        if self.is_token_ready == false {
            match self.working_token {
                Tokens::SeparatorUncomplete(id, line, column) => {
                    self.tokens
                        .push(Token::new(Tokens::Separator, Pos::new(line, column)));
                    self.column += id;
                }
                Tokens::Comment => {
                    self.line += 1;
                    self.column = 1;
                }
                _ => {
                    panic!("Unexpected character at {}:{}", self.line, self.column);
                }
            }
        }
        self.tokens
            .push(Token::new(Tokens::EOF, Pos::new(self.line, self.column)));
    }
    pub fn create_and_add(&mut self, captured: u8) {
        self.is_token_ready = false;
        self.create(captured);
        if self.is_token_ready {
            self.tokens.push(Token::new(
                self.working_token.clone(),
                Pos::new(self.line, self.column),
            ));
            self.column += 1;
        }
    }
    pub fn create(&mut self, token: u8) {
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
            b'"' => self.working_token = Tokens::StringUncompleted(Vec::new(),false),
            b'\n' => {
                self.line += 1;
                self.column = 1;
                self.working_token = Tokens::SeparatorUncomplete(1, self.line, self.column);
            }
            _ => {
                if token.is_ascii_digit() || token == b'.' {
                    let mut ar = [0; 40];
                    ar[0] = token;
                    self.working_token = Tokens::Number(ar, 0, false);
                } else if token.is_ascii_alphabetic() || token == b'_' {
                    let mut ar = [0; 200];
                    ar[0] = token;
                    self.working_token = Tokens::IdentifierUncomplete(ar, 0);
                } else if token.is_ascii_whitespace() {
                    self.working_token = Tokens::SeparatorUncomplete(1, self.line, self.column);
                } else {
                    self.working_token = Tokens::Unknown;
                    self.is_token_ready = true;
                }
            }
        };
    }
}
pub struct Token {
    pub pos: Pos,
    pub token: Tokens,
}

impl Token {
    pub fn new(token: Tokens, pos: Pos) -> Self {
        Self { token, pos }
    }
}
impl Clone for Token {
    fn clone(&self) -> Self {
        Self {
            pos: self.pos,
            token: self.token.clone(),
        }
    }
}
