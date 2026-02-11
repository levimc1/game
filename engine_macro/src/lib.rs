use proc_macro::TokenStream;
use syn::punctuated::Punctuated;
use syn::{LitStr, Error, parse_macro_input, Token};
use quote::quote;
use std::fs;
use std::ffi;
use std::path::PathBuf;
use std::io::BufReader;
use std::io::BufRead;
use std::fs::File;

// engine
// hi from another crate!

// Összes rust path összegyűjtése.
//
// Példa:
// fileok:
// path /
//  main.rs
//  idk /
//  other.rs
//
// main.rs-t észreveszi és resulthoz adódik
// idk/ -n fut read_rust_files()
//  érzékeli a other.rs-t és hozzáadja
//  visszatér result-al
// resultot hozzáadja resulthoz
// resultban minden
fn read_rust_files(dir: PathBuf) -> Result<Vec<PathBuf>, std::io::Error>{
    // PathBuf megy de Path nem. vmi ref-ekkel

    let mut result = Vec::new();

    for entry in fs::read_dir(dir)? {
        
        // ?-eknek nézz jobban utána
        let entry = entry?;
        let path = entry.path();

        
        if (path.is_file() && path.extension() == Some(std::ffi::OsStr::new("rs"))) {
            result.push(path);
        }
        else if (path.is_dir()) {
            if let Ok(mut values) = read_rust_files(path) {
                result.append(&mut values); 
            }
        }
    } 
    Ok(result)

}

// Rust file pathok alapján kinyeri az érintett kommenteket.
//
// Fejlesztések: 
// - Comment helyett üres macro, így runtime metaadat/azonosító objektumban lesz MÁR OTT.
// (nem üres, generálhat dolgokat)
//
// Példa:
// input: 
// // engine
// // module {
// // ...
// // // Comment comment comment dik
// // }
//
// // engine
// // ...
//
// 1 - // engine            -> reading = true, continue
// 2 - // module            -> read 0
// 3 - // ...               -> read 0
// 4 - // // ...            -> continue
// 5 - // }                 -> read 0 
// 6 - //                   -> reading = false, current = 1
// 7 - // engine            -> reading = true, continue
// 8 - // ...               -> read 1
fn gather_comment_lines(path: PathBuf) -> Result<Vec<String>, std::io::Error> {
    
    let mut result : Vec<String> = Vec::new();
    
    let file = File::open(&path)?;
    let reader = BufReader::new(file);
    let mut reading : bool = false;

    for line in reader.lines() {
        let line: String = line?;
        if (line.trim_start().starts_with("// engine")) {
            reading = true;
            continue;
        }
        if (line.trim_start().starts_with("// //")) {continue;}
        if (reading && !line.trim_start().starts_with("// ")) {
            reading = false;
        }   
        if (reading) {result.push(line.chars().skip(3).collect::<String>());}
        // // module Name {} -> module name
    }

    Ok(result)
}
/*
// ja
struct Systems {
    condition: String,
    systems: Vec<String>
}

// struct arra hogy jól eltudjuk tárolni a cuccokat
struct ModuleDecs {
    name: String,
    systems: Vec<Systems>,
}

// Comment sorokból ModuleDesc-t csinál
//
// ennek folyamata:
//
//
//
//
fn parse_comment_lines(lines: Vec<String>) {
    
    

}*/


fn stuff(paths: Vec<PathBuf>) -> Result<TokenStream, std::io::Error> {
    
    // a név rossz :(
    let mut lines: Vec<String> = Vec::new();

    for path in paths {
        let file_paths = read_rust_files(path)?;
    
        for fpath in file_paths {
            lines.extend(gather_comment_lines(fpath)?);
        }
    }
        
    println!("{:?}", lines);

    Ok(quote! {
        println!("sigma");
    }.into())
}

#[proc_macro]
pub fn engine_main(input: TokenStream) -> TokenStream {

    let value = parse_macro_input!(input with Punctuated<LitStr, Token![,]>::parse_terminated);
    
    let mut paths : Vec<PathBuf> = Vec::new();
    for lit in value {
        paths.push(PathBuf::from(lit.value()));
    }
    println!("{:?}", paths);
    
    // mivel macro nem adhat vissza akármit ami nem TokenStream.
    match stuff(paths) {
        Ok(tokens) => return tokens,
        Err(e) => Error::new(proc_macro2::Span::call_site(), e.to_string())
            .to_compile_error()
            .into(),
    }

}
