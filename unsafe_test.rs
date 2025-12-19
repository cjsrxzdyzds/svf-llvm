fn main() {
    let x = 10;
    unsafe {
        let y = &x as *const i32;
        let z = *y;
    }
}
