import unittest
from languages.python.src.ch01_basics.example import add, hello


class TestBasics(unittest.TestCase):
    def test_add(self):
        self.assertEqual(add(2, 3), 5)
        self.assertEqual(add(-1, 1), 0)

    def test_hello(self):
        self.assertEqual(hello("World"), "Hello, World!")
        self.assertTrue(hello("Alice").startswith("Hello"))


if __name__ == "__main__":
    unittest.main()
