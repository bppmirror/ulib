import serial, sys

s = serial.Serial('/dev/ttyU0', 115200, timeout =2)
ret = 0

while True:
    l = s.readline()
    if l.startswith('>>>>>>>>>>> STARTING USER CODE'):
         break

while True:
    l = s.readline()
    if l.startswith('<<<<<<<<<<< USER CODE ENDS'):
         break
    print l,
    if "!FAILED" in l: ret = 1

sys.exit(ret)