#!/bin/bash

version=2012
version=2019
combine=${version}
sources=($(ls ${version}/*.cpp))
cat /dev/null > ${combine}.cpp
for (( i=0; i<${#sources[@]}; i=i+1 ))
do
    source=${sources[$((i+0))]}
    echo "/* ${source} */" >> s.cpp
    cat ${source} >> s.cpp
    echo "" >> s.cpp
    cat ${combine}.cpp s.cpp > t.cpp && mv t.cpp ${combine}.cpp
    rm -f s.cpp
done

