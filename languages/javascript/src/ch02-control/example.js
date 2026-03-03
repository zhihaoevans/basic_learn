function isEven(n) {
  return n % 2 === 0
}

function sumToN(n) {
  let total = 0
  for (let i = 1; i <= n; i++) total += i
  return total
}

module.exports = { isEven, sumToN }
