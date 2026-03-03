pub fn add(a: i32, b: i32) -> i32 {
    a + b
}

pub fn hello(name: &str) -> String {
    format!("Hello, {}!", name)
}

pub fn is_even(n: i32) -> bool {
    n % 2 == 0
}

pub fn sum_to_n(n: u32) -> u32 {
    (1..=n).sum()
