const test = require('node:test')
const assert = require('node:assert')
const { isEven, sumToN } = require('../../src/ch02-control/example')

test('isEven works', () => {
  assert.strictEqual(isEven(2), true)
  assert.strictEqual(isEven(3), false)
  assert.strictEqual(isEven(0), true)
})

test('sumToN works', () => {
  assert.strictEqual(sumToN(1), 1)
  assert.strictEqual(sumToN(5), 15)
  assert.strictEqual(sumToN(0), 0)
})
