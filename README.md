# uLib

Tiny library for embedded

Currently supported platforms:

* PC - pc with Qt5 core library for operation systems cross build
* esp32 - esp32 chip

## Assumptions and dependencies:

###Common
Library needs standard C library (***stdc***) and assumed that it is present on target platform. Also (obvious) C++ runtime should be present also. But stdc++ library is not dependency

###PC

* ***Qt5 core*** lib should be present


* ***esp32***

Nothing more than ***esp32 SDK*** provided

##Directories

* [apps](./apps/Readme.md)
Demo applications. Each application can be build for all of supported platforms

* [doc](./doc/Readme.md)
Main documentation

* ***inc*** - uLib public includes

* ***mk*** - build failes for lib and demo applications

* ***src*** - sources

* ***tests*** - unit tests