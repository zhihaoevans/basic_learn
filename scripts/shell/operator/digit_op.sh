#!/bin/bash

a=10
b=3

#digt math operation
echo "a is $a, b is $b"
echo "a+b: $((a+b))"
echo "a-b: $((a-b))"
echo "a*b: $((a*b))"
echo "a/b: $((a/b))"
echo "a%b: $((a%b))"

#digit compare operation
if [[ $a == $b ]]; then
    echo "a equal to b"
fi

if [[ $a != $b ]]; then
    echo "a is not equal to b"
fi

if [[ $a -eq $b ]]; then
    echo "a equal to b"
fi

if [[ $a -ne $b ]]; then
    echo "a is not equal to b"
fi

if [[ $a -gt $b ]]; then
    echo "a greater than b"
fi

if [[ $a -lt $b ]]; then
    echo "a less than b"
fi

if [[ $a -ge $b ]]; then
    echo "a greater than b, or equal to b"
fi

if [[ $a -le $b ]]; then
    echo "a less than b, or equal to b"
fi

