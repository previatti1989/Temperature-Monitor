Temperature Monitoring System - C Version

Open a terminal and navigate to the project folder
Compile:
gcc:
1. gcc main.c adc_handler.c eeprom_handler.c led_controller.c -o temperature_monitor.exe
2. ./temperature_monitor.exe
msvc:
1. cl main.c adc_handler.c eeprom_handler.c led_controller.c
2. ./main.exe
cmake:
mkdir build
cd build
cmake -G Ninja ..
ninja
./TemperatureMonitor.exe

if bash does not recognize .exe
cmd.exe /c TemperatureMonitor.exe
./TemperatureMonitor.exe

The program will simulate temperature readings from -5 to 120 (system config) degrees Celsius and display LED statuses based on temperature conditions