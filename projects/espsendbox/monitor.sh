#!/bin/sh

PROJECT_NAME="esp_sandbox"

. ./serial.inc

echo "Using device: ${SERIAL}"

python /home/yurkis/esp/esp-idf/tools/idf_monitor.py --baud 115200 --port "${SERIAL}" --toolchain-prefix "xtensa-esp32-elf-" --make "make" --print_filter "" build/${PROJECT_NAME}.elf
