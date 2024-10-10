mod compiling;
mod lexer;
mod parser;
mod pos;
mod scene_system;

use crate::{compiling::compiler::Compiler, parser::parser::Parser};
use lexer::{Lexer, Token};
use std::ffi::CStr;
use std::os::raw::c_char;
use std::ptr::null_mut;
use std::{env, fs};

fn main() {
    let args: Vec<String> = env::args().collect();

    //let args = vec!["./nsr.exe" , "../../../example/Config.ningin" ,  "../../../example/Scene.ningin" , "../../../Ningin/target/debug/Scene"]; 

    if args.len() < 4 {
      panic!("Usage : nsr <Config-Path> <path> <output-path>");
    }

    let configpath = &args[1];
    let path = &args[2];
    let outpath = &args[3];
    let mut compiler = Compiler::from(configpath);
    let file = fs::read_to_string(path).unwrap();
    //Lex
    let mut lexer = Lexer::new(file.len());
    lexer.lex(file);
    //parse
    let mut parser = Parser::new(lexer.tokens, 0);
    parser.parse();
    //compile
    compiler.compile(&mut parser.scene);
    //write
    if let Err(er) = compiler.write_to(outpath) {
        panic!("Failed To Write Into File : {}", er.to_string())
    }
}

#[no_mangle]
pub extern "C" fn getTokens(file_input: *const c_char, out_size : *mut i32) -> *mut Token {
  let c_str = unsafe { CStr::from_ptr(file_input) };
  let file_input_str = match c_str.to_str() {
      Ok(s) => s,
      Err(_) => {return null_mut();}, // Return error code if invalid string
  };

  let mut lexer = Lexer::new(file_input_str.len());
  lexer.lex(file_input_str.to_string());
  let tokens = lexer.tokens;
  let size = tokens.len();
  let token_array = tokens.into_boxed_slice();
  unsafe {
    *out_size = size as i32;
  }
  Box::into_raw(token_array) as *mut Token
}