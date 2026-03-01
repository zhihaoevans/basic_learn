import unittest
import subprocess
import os

class TestHello(unittest.TestCase):
    def test_output(self):
        p = subprocess.run(["python", os.path.join(os.path.dirname(__file__), "hello.py")], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        self.assertEqual(p.stdout.strip(), "Hello, Python")
        self.assertEqual(p.returncode, 0)

if __name__ == "__main__":
    unittest.main()
