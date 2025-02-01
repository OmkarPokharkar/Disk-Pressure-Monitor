#!/bin/sh

# Compile the code
make

# Move the binary to /usr/local/bin with the name 'dpm'
sudo mv disk_pressure_monitor /usr/local/bin/dpm

# Clean up object files
make clean

echo "Installation complete. You can now use the tool by running 'dpm' from the command line."
echo "Example usage: dpm --path / --threshold 80 --interval 60"
