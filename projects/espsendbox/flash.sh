#!/bin/sh

PROJECT_NAME="esp_sandbox"

. ./serial.inc

echo "Using device: ${SERIAL}"


#python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port "/dev/ttyUSB0" --baud 115200 --before "default_reset" --after "hard_reset" write_flash -z --flash_mode "dio" --flash_freq "40m" --flash_size detect   0x1000 build/bootloader/bootloader.bin 0x10000 build/${PROJECT_NAME}.bin 0x8000 build/partition_table/partition-table.bin

python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port "${SERIAL}" --baud 115200 --before "default_reset" --after "hard_reset" write_flash -z --flash_mode "dio" --flash_freq "40m" --flash_size detect   0x1000 build/bootloader/bootloader.bin 0x10000 build/${PROJECT_NAME}.bin 0x8000 build/partition_table/partition-table.bin
