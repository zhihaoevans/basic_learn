use learn_basic_rust::{is_even, sum_to_n};

#[test]
fn test_is_even() {
    assert!(is_even(2));
    assert!(!is_even(3));
    assert!(is_even(0));
}

#[test]
fn test_sum_to_n() {
    assert_eq!(sum_to_n(1), 1);
    assert_eq!(sum_to_n(5), 15);
    assert_eq!(sum_to_n(0), 0);
}
