#!/bin/bash

if ! command -v python3 >/dev/null 2>&1; then
	echo "Python3 is not installed. Please install it."
	exit 1
fi

python3 -m pip3 install norminette --user --upgrade --quiet

python3 -m norminette "$@"
