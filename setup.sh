#!/bin/bash

# Check if the script is running as root (sudo)
if [ "$(id -u)" != "0" ]; then
    echo "This script needs to be run with sudo or as root."
    exit 1
fi

# Update package lists and install packages
apt update
apt install -y alsa-utils
