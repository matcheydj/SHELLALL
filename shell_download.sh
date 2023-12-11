#!/bin/bash

# Define directory for non-open-source shells
NOS_DIR="NOS"

# Create the directory if it doesn't exist
mkdir -p "$NOS_DIR"

# Function to install a shell
install_shell() {
  echo "Installing $1..."
  sudo apt-get install -y "$1"
}

# Install open-source shells
install_shell tcsh
install_shell sh
install_shell ksh
install_shell fish
install_shell dash
install_shell ash
install_shell nu

# Download non-open-source shells (adjust URLs based on license terms)
echo "Downloading non-open-source shells..."
# rc shell (Ratliff shell)
# wget -P "$NOS_DIR" https://github.com/rcsh/rc/archive/refs/tags/rc-1.8.7.tar.gz

# mksh (MirBSD Korn Shell)
# wget -P "$NOS_DIR" https://ftp.mirbsd.org/mirbsd/mksh/mksh-61.0.tar.gz

# busybox ash shell (part of busybox)
# wget -P "$NOS_DIR" https://busybox.net/downloads/busybox-1.35.0.tar.bz2

# Example download for a non-open-source shell (replace with actual URL)
wget -P "$NOS_DIR" https://example.com/non-open-source-shell.tar.gz

echo "Done."
