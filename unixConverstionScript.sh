#!/bin/bash
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
echo "Script directory: $SCRIPT_DIR"
find . -type f -exec dos2unix -b {} \;
