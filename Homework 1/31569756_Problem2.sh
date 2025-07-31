#!/bin/bash

if [ -z "$1" ]; then
    echo "Error: No file name or directory has been provided. Please enter a valid file name or directory:"
    read name
else
    name="$1"
    if [ -z "$name" ]; then
        echo "Error: There wasn't a file or directory provided."
        exit 0
    fi
fi

echo "You entered: $name"

if [ -d "$name" ] || [ -f "$name" ]; then
    if [ -d "$name" ]; then
        if [ -r "$name" ] && [ -x "$name" ]; then
            fileCount=0
            dirCount=0
            for item in "$name"/*; do
                [ -e "$item" ] || continue
                if [ -f "$item" ]; then
                    fileCount=$((fileCount + 1))
                elif [ -d "$item" ]; then
                    dirCount=$((dirCount + 1))
                fi
            done
            echo "Number of files: $fileCount"
            echo "Number of subdirectories: $dirCount"
            echo "Listing the files and directories with sizes:"
            ls -lh "$name"
        else
            echo "You do NOT have the read and/or execute permissions for the directory: $name"
        fi
    elif [ -f "$name" ]; then
        if [ -r "$name" ]; then
            wordCount=$(wc -w < "$name")
            lineCount=$(awk 'END {print NR}' "$name")
            charCount=$(wc -m < "$name")
            echo "Word Count: $wordCount"
            echo "Line Count: $lineCount"
            echo "Character Count: $charCount"
            if [ "$charCount" -gt 10000 ]; then
                echo "Category: Text Heavy"
            elif [ "$charCount" -ge 1000 ]; then
                echo "Category: Moderately Sized"
            else
                echo "Category: Light File"
            fi
        else
            echo "You do NOT have read permissions for '$name'."
        fi
    fi
fi
