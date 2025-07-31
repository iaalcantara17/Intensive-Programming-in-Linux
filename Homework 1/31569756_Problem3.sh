#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo "Error: You need to enter at least three filenames."
    exit 99
fi

today=$(date +"%Y%m%d")
backupFolder="backup_$today"
mkdir "$backupFolder"
logFile="$backupFolder/backupLog.txt"
echo "Backup Log - $today" > "$logFile"

for file in "$@"; do
    if [ -f "$file" ]; then
        newName="${file}_$today"
        cp "$file" "$backupFolder/$newName"
        echo "$file -> $newName" >> "$logFile"
        echo "Copied: $file"
    else
        echo "Skipping: $file not found"
    fi
done

echo "Backup complete! Saved in: $backupFolder"

