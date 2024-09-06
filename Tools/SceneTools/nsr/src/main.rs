mod compiling;
mod lexer;
mod parser;
mod pos;
mod scene_system;

use crate::{compiling::compiler::Compiler, parser::parser::Parser};
use lexer::Lexer;
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
