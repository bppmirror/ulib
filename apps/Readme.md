# uLib demo applications

* [app_template](./app_template/Readme.md)

Empty demo application template

* [log_demo](./log_demo/Readme.md)

Logger demo application

* [playground](./playground/Readme.md)

Sandbox for experiments

## Development environment

### Common and PC target
For general build ***cmake*** should be installed. For PC build at least ***Qt5 core*** library should be installed

```
Linux (Ubuntu):
% sudo apt-get install cmake build-essential qtbase5-dev

FreeBSD:
# pkg install cmake qt5

```

### ESP32 target
For esp32 cmake is still needed (see above). Also you need ESP SDK. See [ESP32 Get started document](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html)
**ISP_PATH** environment variable should point to ESP-IDF as described in "Get started" ESP documentation

## How to build and run

Dependencies are:

* **PC build** - Qt5 core library
* **esp32** - esp32 toolchain and IDF SDK. IDF_PATH environment variable should point to IDF SDK!

Each directory contains those files:

* **build.sh** - build application. If called without params build for pc if param is *esp32* app will be built for esp32

Example:
```
Build for PC:
./build sh

Build for ESP32: 
./build.sh esp32
```
* **run.sh** - run application.  If called without means pc if param is *esp32* app will flashed and run on esp32 chip

For PC application will run
For esp32 chip will be flashed and monitor will be started. 
Default USB serial port for esp32 platfrom is /dev/ttyUSB0. For FreeBSD default is /dev/cuaaU0 . You may specify port by third script param

Example:
```
Run at PC:
./run sh

Run at ESP32 with default USB serial: 
./run.sh esp32


Run at ESP32 with custom USB serial: 
./run.sh esp32 /dev/ttyUSB1

```

* **clean.sh** - clean all

## Technical notes

[Technical details about apps build system you may found in app_Template readme file](./app_template/Readme.md)