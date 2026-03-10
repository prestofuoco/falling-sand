#!/bin/bash

ELF_FILE="./build/Debug/src.elf"

if [ ! -f "$ELF_FILE" ]; then
    echo "ELF file not found at $ELF_FILE. Did you build the project?"
    exit 1
fi

TEMP_BIN=$(mktemp)

echo "Converting ELF to BIN..."
arm-none-eabi-objcopy -O binary "$ELF_FILE" "$TEMP_BIN"

echo "Flashing via DFU..."
dfu-util -a 0 -s 0x08000000:leave -D "$TEMP_BIN"

rm "$TEMP_BIN"

echo "Done!"