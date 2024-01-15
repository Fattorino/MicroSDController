# MicroSDController
**Simple library to handle SD cards with ESP32**

A simple library to manage SD cards with the standard File System.

## Features
- Manage SD card information
- Create and remove directories
- Create and remove files
- Read and write files on the fly

## Implementation (In a PlatformIO project)
### Quick:
    lib_deps =
        . . .
        https://github.com/Fattorino/MicroSDController.git#v1.0.0

### Manual:
1. Download the latest .zip from the release page;
2. Copy the MicroEspSockets folder into the lib folder of your PlatformIO project;
3. Use ```#include <MicroSDController.h>```

## Basic Usage
```c++
#include <Arduino.h>
#include <vector>
#include <MicroSDController.h>

int attempts = 0;

void setup()
{
    Serial.begin(9600); Serial.print("\n");
    
    // Initialize Micro SD
    while (!SDC::init() && attempts < 15)
        attempts++;

    if (!SDC::ready()) { Serial.println("Init Failed!"); return; }

    // Create a file in root called "test1.txt"
    LogFile test1("/test1.txt");

    // Create a directory in root called "dir"
    SDC::makedir("/dir");
    
    // Create a file inside "dir" called "test2.txt"
    LogFile test2("dir/test2.txt");
    
    // List files in root
    std::vector<String> list = SDC::listFiles("/");
    Serial.println("FILEs LIST:");
    for (String &s : list) { Serial.println(s); }
    
    // List directories in root
    std::vector<String> list = SDC::listDirs("/");
    Serial.println("DIRs LIST:");
    for (String &s : list) { Serial.println(s); }
}

void loop() { }
```


