SERIAL=$2
FREEBSD_SERIAL="/dev/cuaU0"
LINUX_SERIAL="/dev/ttyUSB0"

if [ -z "$SERIAL" ]; then
    if [ -e  "${FREEBSD_SERIAL}" ]; then
	SERIAL="${FREEBSD_SERIAL}"
    else if [ -e "${LINUX_SERIAL}" ]; then
	SERIAL="${LINUX_SERIAL}"
	else
        echo "Default USB serial not found! Please specify as parameter!"
    fi
    fi
fi
