#!/bin/bash
declare -A site
site["google"]="www.google.com"
site["runoob"]="www.runoob.com"
site["taobao"]="www.taobao.com"

#get element
echo "${site["google"]}"
echo "${site["runoob"]}"
echo "${site["taobao"]}"

#get all element
echo "elements: ${site[*]}"
echo "elements: ${site[@]}"

#get all element index
echo "index of element: ${!site[*]}"
echo "index of element: ${!site[@]}"

#get length of arr
echo "number of element: ${#site[*]}"
echo "number of element: ${#site[@]}"

