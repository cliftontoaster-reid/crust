#!/bin/bash

if ! command -v python3 >/dev/null 2>&1; then
	echo "Python3 is not installed. Please install it."
	exit 1
fi

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 file(s)"
	exit 1
fi

python3 -m pip3 install c_formatter_42 --user --upgrade --quiet

for file in "$@"; do
	if [[ ! -f ${file} ]]; then
		echo "File not found: ${file}"
		continue
	fi

	tmpfile=$(mktemp /tmp/format.XXXXXX)
	cp "${file}" "${tmpfile}"

	# Format the temporary file
	python3 -m c_formatter_42 "${tmpfile}"

	# Compare with the original; replace if they differ.
	if ! diff -q "${file}" "${tmpfile}" >/dev/null 2>&1; then
		cp "${tmpfile}" "${file}"
		echo "Reformatted: ${file}"
	else
		echo "No formatting changes needed for: ${file}"
	fi

	rm "${tmpfile}"
done
