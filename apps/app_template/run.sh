#!/bin/sh
BASEDIR=$(dirname "$0")
CURRDIR=$(dirname 'pwd')

PROJECT_NAME=app_template

if [ "$1" = "esp32" ] ; then
. ./serial.inc

echo " ============> Flashing ......"
echo "Using device: ${SERIAL}"

python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port "${SERIAL}" --baud 115200 --before "default_reset" --after "hard_reset" write_flash -z --flash_mode "dio" --flash_freq "40m" --flash_size detect   0x1000 ${BASEDIR}/build/esp/bootloader/bootloader.bin 0x10000 ${BASEDIR}/build/esp/${PROJECT_NAME}.bin 0x8000 ${BASEDIR}/build/esp/partition_table/partition-table.bin

echo " =============> Starting monitor ...."
python /home/yurkis/esp/esp-idf/tools/idf_monitor.py --baud 115200 --port "${SERIAL}" --toolchain-prefix "xtensa-esp32-elf-" --make "make" --print_filter "" ${BASEDIR}/build/esp/${PROJECT_NAME}.elf

else

${BASEDIR}/build/pc/${PROJECT_NAME}

fi
