#!/bin/bash

dict="dictionary.txt"

grep -Ei "a.*a.*a" "$dict" > tempA
countA=$(wc -l < tempA)
echo $countA

grep -Ei "^[^eE]*[eE][^eE]+[eE][^eE]+[eE][^eE]*$" "$dict" > tempE
countE=$(wc -l < tempE)
echo $countE

grep -Ei "ee" "$dict" > tempEE
grep -Eo ".{3}$" tempEE > tempLast
sort tempLast > tempSorted
uniq -c tempSorted > tempCount
sort -nr tempCount | head -3

rm tempA tempE tempEE tempLast tempSorted tempCount

