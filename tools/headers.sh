#!/bin/bash
set -euo pipefail

# Define source and destination directories
src_dir="includes"
dest_dir="build/include"

# Check if source directory exists
if [ ! -d "$src_dir" ]; then
  echo "Source directory '$src_dir' does not exist."
  exit 1
fi

# Create destination directory if needed
mkdir -p "$dest_dir"

# Find and copy files not ending with .int.h while preserving the directory structure
find "$src_dir" -type f ! -name '*.int.h' | while IFS= read -r file; do
  # Remove the source directory prefix from the file path
  relative_path="${file#$src_dir/}"
  dest_file="$dest_dir/$relative_path"

  # Ensure the destination subdirectory exists
  mkdir -p "$(dirname "$dest_file")"

  # Copy the file
  cp "$file" "$dest_file"

  # Print the copied file
  echo "Copied '$file' to '$dest_file'"
done
