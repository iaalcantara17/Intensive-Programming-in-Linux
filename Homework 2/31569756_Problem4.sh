#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <File>"
    exit 1
fi

inFile="$1"

if [ ! -f "$inFile" ]; then
    echo "Error: File does not exist."
    exit 1
fi

cYear=2024
arr=()

while IFS=',' read -r name dob city country || [ -n "$name" ]; do
    city="$(echo "$city" | tr -d '"')"
    if echo "$city" | grep -q ' '; then
        if echo "$dob" | grep -qE '^[0-9]{4}-[0-9]{2}-[0-9]{2}$'; then
            bYear="$(echo "$dob" | cut -d '-' -f1)"
            age=$((cYear - bYear))
            arr+=("$age,$name")
        fi
    fi
done < "$inFile"

if [ ${#arr[@]} -eq 0 ]; then
    echo "No valid entries found."
    exit 1
fi

IFS=$'\n' sorted=($(printf "%s\n" "${arr[@]}" | sort -nr))

for person in "${sorted[@]}"; do
    pAge="$(echo "$person" | cut -d',' -f1)"
    pName="$(echo "$person" | cut -d',' -f2-)"
    echo "$pName, $pAge years old"
done
