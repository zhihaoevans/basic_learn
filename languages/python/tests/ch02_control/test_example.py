import unittest
from languages.python.src.ch02_control.example import is_even, sum_to_n


class TestControl(unittest.TestCase):
    def test_is_even(self):
        self.assertTrue(is_even(2))
        self.assertFalse(is_even(3))
        self.assertTrue(is_even(0))

    def test_sum_to_n(self):
        self.assertEqual(sum_to_n(1), 1)
        self.assertEqual(sum_to_n(5), 15)
        self.assertEqual(sum_to_n(0), 0)


if __name__ == "__main__":
    unittest.main()
