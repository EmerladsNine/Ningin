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
                Tokens::Separator => {
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
                Tokens::Separator => {
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
            Tokens::IntegerNumber(..) => {
                value = token.clone();
            }
            Tokens::DecimalNumber(..) => {
                value = token.clone();
            }

            Tokens::Plus => {
                let mut tok = self.parse_factor();
                match tok.token {
                    Tokens::IntegerNumber(val) => {
                        tok.token = Tokens::IntegerNumber(val);
                        value = tok;
                    }

                    Tokens::DecimalNumber(val) => {
                        tok.token = Tokens::DecimalNumber(val);
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
                    Tokens::IntegerNumber(val) => {
                        tok.token = Tokens::IntegerNumber(-val);
                        value = tok;
                    }

                    Tokens::DecimalNumber(val) => {
                        tok.token = Tokens::DecimalNumber(-val);
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
            Tokens::Separator => {
                return self.parse_factor();
            }
            _ => {
                panic!("Expected a number at {}", pos)
            }
        };
        value
    }

    pub fn operate(&mut self, first: Token, second: Token, operation: Token) -> Token {
        let mut token = Token::new(Tokens::Separator, first.pos);

        match first.token {
            Tokens::IntegerNumber(val1) => match second.token {
                Tokens::IntegerNumber(val2) => {
                    token.token = self.integer_operation(val1, val2, operation);
                }
                _ => {
                    panic!("Expected a numeric value at {}", second.pos)
                }
            },

            Tokens::DecimalNumber(val1) => match second.token {
                Tokens::DecimalNumber(val2) => {
                    token.token = self.decimal_operation(val1, val2, operation);
                    //decimal operation
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
    pub fn decimal_operation(&mut self, first: f64, second: f64, operation: Token) -> Tokens {
        match operation.token {
            Tokens::Times => {
                let num = first * second;
                return Tokens::DecimalNumber(num);
            }
            Tokens::Divide => {
                let num = first / second;
                return Tokens::DecimalNumber(num);
            }
            Tokens::Plus => {
                let num = first + second;
                return Tokens::DecimalNumber(num);
            }
            Tokens::Minus => {
                let num = first - second;
                return Tokens::DecimalNumber(num);
            }
            _ => {}
        }
        panic!("Failed to Parse Math Operation at {}", operation.pos)
    }
    pub fn integer_operation(&mut self, first: i128, second: i128, operation: Token) -> Tokens {
        match operation.token {
            Tokens::Times => {
                let num = first * second;
                return Tokens::IntegerNumber(num);
            }
            Tokens::Divide => {
                let num = first / second;
                return Tokens::IntegerNumber(num);
            }
            Tokens::Plus => {
                let num = first + second;
                return Tokens::IntegerNumber(num);
            }
            Tokens::Minus => {
                let num = first - second;
                return Tokens::IntegerNumber(num);
            }
            _ => {
                panic!("Failed to Parse Math Operation at {}", operation.pos)
            }
        }
    }
}
