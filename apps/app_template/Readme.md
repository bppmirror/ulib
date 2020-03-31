# uLib app template

## How to run and build
[see general description for apps](../Readme.md)

## How to use

1. Copy template somewere in apps directory

2. Change **project name** and **TARGET** variable in CMakeLists.txt file

3. Change **PROJECT_NAME** variable in run.sh with your app name
**Application ame should be equal for both this locations**

4. If you need more .cpp files in build  you can ad this files to **APP_SRC** variable in CMakeLsists.txt

### How to move app outside uLib apps directory

1. Change **ULIB_DIR** variable in CMakeLists.txt file. This variable should point to uLib sources root


### Wrappers and startup

This app contains simple wrappers for each platform. 

* For PC wrapper contains only C main() function that calls **start_app()** function and exit

* On esp32 wrapper show some information, call **start_app()** function and reset chip in 30 seconds

You may change this behaviour by editing platform dependent sources in wrappers/ directory

