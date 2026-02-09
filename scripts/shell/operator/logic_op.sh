#!/bin/bash

if  true; then
    echo "true is true"
fi

if  ! false; then
    echo "! false is true"
fi

if  true -o false ; then
    echo "true -o false is true"
fi

if  true -a false ; then
    echo "true -a false is true" #print this, why?
else 
    echo "true -a false is false"
fi

if  true || false ; then
    echo "true || false is true"
fi

if  true && false ; then
    echo "true && false is true"
else 
    echo "true && false is false"
fi

