use std::{os::raw::c_void, ptr::null_mut};

use crate::{
    lexer::{Token, Tokens},
    parser::parser::Parser,
};

impl Parser {
    pub fn parse_expression(&mut self) -> Token {
        let mut value = self.parse_term();
        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::Plus => {
                    self.pos += 1;
                    let val2 = self.parse_term();
                    value = self.operate(value, val2, token);
                }
                Tokens::Minus => {
                    self.pos += 1;
                    let val2 = self.parse_term();
                    value = self.operate(value, val2, token);
                }
                Tokens::Separator | Tokens::Comment => {
                    self.pos += 1;
                }
                _ => {
                    break;
                }
            }
        }
        value
    }

    pub fn parse_term(&mut self) -> Token {
        let mut value = self.parse_factor();
        loop {
            let token = self.peek().unwrap().clone();
            match token.token {
                Tokens::Times => {
                    self.pos += 1;
                    let val2 = self.parse_factor();
                    value = self.operate(value, val2, token);
                }

                Tokens::Divide => {
                    self.pos += 1;
                    let val2 = self.parse_factor();
                    value = self.operate(value, val2, token);
                }
                Tokens::Separator | Tokens::Comment=> {
                    self.pos += 1;
                }
                _ => {
                    break;
                }
            }
        }
        value
    }

    pub fn parse_factor(&mut self) -> Token {
        let token = self.advance().unwrap();
        let pos = token.pos.clone();
        let value;
        match token.token {
            Tokens::IntegerNumber => {
                value = token.clone();
            }
            Tokens::DecimalNumber => {
                value = token.clone();
            }

            Tokens::Plus => {
                let tok = self.parse_factor();
                match tok.token {
                    Tokens::IntegerNumber => {
                        value = tok;
                    }

                    Tokens::DecimalNumber => {
                        value = tok;
                    }

                    _ => {
                        panic!("Expected a number at {}", pos)
                    }
                }
            }

            Tokens::Minus => {
                let mut tok = self.parse_factor();
                match tok.token {
                    Tokens::IntegerNumber => {
                        let val_ptr = tok.value as *mut i128;
                        let val = unsafe {
                            *val_ptr
                        };
                        tok.value = Box::into_raw(Box::new(-val)) as *mut c_void;
                        value = tok;
                    }

                    Tokens::DecimalNumber => {
                        let val_ptr = tok.value as *mut f64;
                        let val = unsafe {
                            *val_ptr
                        };
                        tok.value = Box::into_raw(Box::new(-val)) as *mut c_void;
                        value = tok;
                    }

                    _ => {
                        panic!("Expected a number at {}", pos)
                    }
                }
            }

            Tokens::Lparanth => {
                value = self.parse_expression();
                let tok = self.advance().unwrap();
                match tok.token {
                    Tokens::Rparanth => {}
                    _ => {
                        panic!("Expected closing parenthesis at {}", tok.pos);
                    }
                }
            }
            Tokens::Separator | Tokens::Comment => {
                return self.parse_factor();
            }
            _ => {
                panic!("Expected a number at {}", pos)
            }
        };
        value
    }

    pub fn operate(&mut self, first: Token, second: Token, operation: Token) -> Token {
        let mut token = Token::new(Tokens::Separator,first.start,null_mut(), first.pos);

        match first.token {
            Tokens::IntegerNumber => match second.token {
                Tokens::IntegerNumber => {
                    let val_ptr = first.value as *mut i128;
                    let val1 = unsafe {
                        *val_ptr
                    };
                    let val_ptr = second.value as *mut i128;
                    let val2 = unsafe {
                        *val_ptr
                    };
                    token.token = Tokens::IntegerNumber;
                    token.value = Box::into_raw(Box::new(self.integer_operation(val1, val2, operation))) as *mut c_void;
                }
                _ => {
                    panic!("Expected a numeric value at {}", second.pos)
                }
            },

            Tokens::DecimalNumber => match second.token {
                Tokens::DecimalNumber => {
                    let val_ptr = first.value as *mut f64;
                    let val1 = unsafe {
                        *val_ptr
                    };
                    let val_ptr = second.value as *mut f64;
                    let val2 = unsafe {
                        *val_ptr
                    };
                    //decimal operation
                    token.token = Tokens::DecimalNumber;
                    token.value = Box::into_raw(Box::new(self.decimal_operation(val1, val2, operation))) as *mut c_void;
                }
                _ => {
                    panic!("Expected a numeric value at {}", second.pos)
                }
            },

            _ => {
                panic!("Expected a numeric value at {}", first.pos)
            }
        }
        token
    }
    pub fn decimal_operation(&mut self, first: f64, second: f64, operation: Token) -> f64 {
        match operation.token {
            Tokens::Times => {
                let num = first * second;
                return num;
            }
            Tokens::Divide => {
                let num = first / second;
                return num;
            }
            Tokens::Plus => {
                let num = first + second;
                return num;
            }
            Tokens::Minus => {
                let num = first - second;
                return num;
            }
            _ => {}
        }
        panic!("Failed to Parse Math Operation at {}", operation.pos)
    }
    pub fn integer_operation(&mut self, first: i128, second: i128, operation: Token) -> i128 {
        match operation.token {
            Tokens::Times => {
                let num = first * second;
                return num;
            }
            Tokens::Divide => {
                let num = first / second;
                return num;
            }
            Tokens::Plus => {
                let num = first + second;
                return num;
            }
            Tokens::Minus => {
                let num = first - second;
                return num;
            }
            _ => {
                panic!("Failed to Parse Math Operation at {}", operation.pos)
            }
        }
    }
}
