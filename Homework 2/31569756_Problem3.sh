#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <Directory>"
    exit 1
fi

dir="$1"

if [ ! -d "$dir" ]; then
    echo "Error: Directory does not exist."
    exit 1
fi

emailList=()

searchFiles() 
{
    for file in "$1"/*; do
        if [ -d "$file" ]; then
            searchFiles "$file"
        elif [ -f "$file" ] && [[ "$file" == *.txt ]]; then
            while IFS= read -r line; do
                emails=$(echo "$line" | grep -oE "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}")
                if [ ! -z "$emails" ]; then
                    emailList+=("$emails")
                fi
            done < "$file"
        fi
    done
}

searchFiles "$dir"

printf "%s\n" "${emailList[@]}" | sort -u > unique_emails.txt

echo "Unique email addresses are now saved in unique_emails.txt"
