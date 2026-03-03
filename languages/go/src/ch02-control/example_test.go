package control

import "testing"

func TestIsEven(t *testing.T) {
	if !IsEven(2) || IsEven(3) || !IsEven(0) {
		t.Fatal("IsEven failed")
	}
}

func TestSumToN(t *testing.T) {
	if SumToN(1) != 1 || SumToN(5) != 15 || SumToN(0) != 0 {
		t.Fatal("SumToN failed")
	}
}
