#!/bin/bash
i=1
for i in {1..10}
do
    echo -e "it is $i\n"
    if [[ $i -eq 5 ]]; then
        echo -e "medium\n"
    fi
done

str="this is a str"
for i in ${str}
do
    echo -e "it is $i\n"
done

for i in $(ls)
do
    ls -alh $i
done
