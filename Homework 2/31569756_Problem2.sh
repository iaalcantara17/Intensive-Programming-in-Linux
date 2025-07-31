#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <C_File>"
    exit 1
fi

cFile="$1"

if [ ! -f "$cFile" ]; then
    echo "Error: File does not exist."
    exit 1
fi

lineCount=$(wc -l < "$cFile")

grep "scanf" "$cFile" >> scanf_log.txt
grep "printf" "$cFile" >> printf_log.txt

scanfCount=$(grep -c "scanf" "$cFile")
printfCount=$(grep -c "printf" "$cFile")

if [ "$lineCount" -eq 0 ]; then
    scanfPercent=0
    printfPercent=0
else
    scanfPercent=$((100 * scanfCount / lineCount))
    printfPercent=$((100 * printfCount / lineCount))
fi

echo "Total lines in file: $lineCount"
echo "Lines containing 'scanf': $scanfCount ($scanfPercent%)"
echo "Lines containing 'printf': $printfCount ($printfPercent%)"
