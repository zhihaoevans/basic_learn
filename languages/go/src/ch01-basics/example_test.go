package basics

import "testing"

func TestAdd(t *testing.T) {
	if Add(2, 3) != 5 {
		t.Fatal("add failed")
	}
	if Add(-1, 1) != 0 {
		t.Fatal("add failed")
	}
}

func TestHello(t *testing.T) {
	if Hello("World") != "Hello, World!" {
		t.Fatal("hello failed")
	}
	if Hello("Alice")[:5] != "Hello" {
		t.Fatal("hello prefix failed")
	}
}
