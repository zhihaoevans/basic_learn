#!/bin/bash

#position parameter
echo "shell name: $0"
echo "first parameter: $1"
echo "second parameter: $2"
echo "third parameter: $3"

#special var to deal parameter
echo "number of para: $#"
echo "para(single str): $*"
echo "para(multiple str): $@"

#special var
echo "process id of current shell: $$"
pwd 
echo "exit code of last cmd: $?"

echo "$-"
echo "$!"