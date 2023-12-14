#!/bin/bash

if [ "$(id -u)" != "0" ]; then
    echo "This script needs to be run with sudo or as root."
    exit 1
fi

apt install -y dos2unix

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
echo "Script directory: $SCRIPT_DIR"
find . -type f -exec dos2unix -b {} \;
