package control

func IsEven(n int) bool {
	return n%2 == 0
}

func SumToN(n int) int {
	total := 0
	for i := 1; i <= n; i++ {
		total += i
	}
	return total
}
