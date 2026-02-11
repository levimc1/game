use engine_macro::engine_main;

// engine
// hi from main crate!

// engine
// vmi
// // vmi2
// vmi3
// vmi4

// engine
// module {
//   systems {
//     ...
//  }
// }

// ["vmi", "vmi3", "vmi4", "vmi6", "vmi7"]  

fn main() {
    engine_main!("/home/lev1/Projects/lev1engine/game/game", "/home/lev1/Projects/lev1engine/game/engine_macro");
    println!("Hello, world!");
}
