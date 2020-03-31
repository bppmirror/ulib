#!/bin/sh
BASEDIR=$(dirname "$0")
CURRDIR=$(dirname 'pwd')

PROJECT_NAME=ulib_tests

. ${BASEDIR}/../serial.inc

echo " ============> Flashing ......"
echo "Using device: ${SERIAL}"

python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port "${SERIAL}" --baud 115200 --before "default_reset" --after "hard_reset" write_flash -z --flash_mode "dio" --flash_freq "40m" --flash_size detect   0x1000 ${BASEDIR}/../tests/build/esp/bootloader/bootloader.bin 0x10000 ${BASEDIR}/../tests/build/esp/${PROJECT_NAME}.bin 0x8000 ${BASEDIR}/../tests/build/esp/partition_table/partition-table.bin
python ${BASEDIR}/ci_tests.py
