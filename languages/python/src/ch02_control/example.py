def is_even(n):
    return n % 2 == 0


def sum_to_n(n):
    total = 0
    for i in range(1, n + 1):
        total += i
    return total
