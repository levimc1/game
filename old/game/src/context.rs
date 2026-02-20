
pub use crate::renderer::Renderer;

pub struct Context {

    // global

    // module
    pub renderer: Renderer,
}

impl Context {

    pub fn new() -> Context {
        Context {
            renderer: Renderer::new(),
        }
    }
}
