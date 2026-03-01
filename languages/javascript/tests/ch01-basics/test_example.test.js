const test = require('node:test')
const assert = require('node:assert')
const { add, hello } = require('../../src/ch01-basics/example')

test('add works', () => {
  assert.strictEqual(add(2, 3), 5)
  assert.strictEqual(add(-1, 1), 0)
})

test('hello formats', () => {
  assert.strictEqual(hello('World'), 'Hello, World!')
  assert.ok(hello('Alice').startsWith('Hello'))
})
