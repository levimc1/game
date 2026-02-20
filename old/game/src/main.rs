
mod renderer;
mod context;

pub use context::{Context, Renderer};

fn main() {
    
    println!("Hello, world!");
    
    let mut ctx = Context::new();

    Renderer::init(&mut ctx);

}
