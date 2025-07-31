#!/bin/bash

while true; do
    read -p "Enter a directory name: " dir
    if [ -d "$dir" ]; then
        cd "$dir"
        break
    else
        read -p "Directory does not exist. Create it? (y/n): " create
        if [ "$create" = "y" ]; then
            mkdir "$dir"
            cd "$dir"
            break
        fi
    fi
done

showFile() {
    file="$1"
    start=1
    totalLines=$(wc -l < "$file")
    while [ "$start" -le "$totalLines" ]; do
        head -n "$((start + 9))" "$file" | tail -n 10
        start=$((start + 10))
        if [ "$start" -gt "$totalLines" ]; then
            break
        fi
        read -p "Do you want to see more? (y/n): " choice
        if [ "$choice" != "y" ]; then
            break
        fi
    done
}

searchModified() {
    local directory="$1"
    [ -d "$directory" ] || return
    local item
    for item in "$directory"/*; do
        [ -e "$item" ] || continue
        if [ -f "$item" ]; then
            now=$(date +%s)
            mod=$(stat -c %Y "$item" 2>/dev/null)
            diff=$((now - mod))
            if [ "$diff" -le 86400 ]; then
                recentFiles+=("$item")
            fi
        elif [ -d "$item" ]; then
            searchModified "$item"
        fi
    done
}

showSubdirectory() {
    subdir="$1"
    cd "$subdir" || return
    echo "Looking for files modified in the last 24 hours (recursively)..."
    recentFiles=()
    searchModified "."
    if [ "${#recentFiles[@]}" -eq 0 ]; then
        echo "No recent files found."
        cd ..
        return
    fi
    echo "Recent files found under '$subdir':"
    select file in "${recentFiles[@]}" "Back"; do
        if [ "$file" = "Back" ]; then
            break
        elif [ -n "$file" ] && [ -f "$file" ]; then
            showFile "$file"
        else
            echo "Invalid choice."
        fi
    done
    cd ..
}

while true; do
    echo "Contents of '$dir':"
    filesAndDirs=(*)
    if [ "${#filesAndDirs[@]}" -eq 0 ]; then
        echo "No files or subdirectories found."
    else
        select item in "${filesAndDirs[@]}" "Exit"; do
            if [ "$item" = "Exit" ]; then
                exit 0
            elif [ -f "$item" ]; then
                showFile "$item"
            elif [ -d "$item" ]; then
                showSubdirectory "$item"
            fi
            break
        done
    fi
done
