#!/bin/bash
arr=(hello world 1 2 3 a b c)

#get array element
echo "${arr[0]}"
echo "${arr[4]}"

#get number of array elememt
echo "${#arr[*]}"
echo "${#arr[@]}"

#get length of a array element
echo "${#arr[0]}"
