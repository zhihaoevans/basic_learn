use learn_basic_rust::{add, hello};

#[test]
fn test_add() {
    assert_eq!(add(2, 3), 5);
    assert_eq!(add(-1, 1), 0);
}

#[test]
fn test_hello() {
    assert_eq!(hello("World"), "Hello, World!");
    assert!(hello("Alice").starts_with("Hello"));
}
