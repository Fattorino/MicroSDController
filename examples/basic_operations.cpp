#include <Arduino.h>
#include <vector>
#include "MicroSDController.h"

int attempts = 0;

void setup()
{
    Serial.begin(9600);
    Serial.print("\n");

    while (!SDC::init() && attempts < 15)
        attempts++;

    if (!SDC::ready())
    {
        Serial.println("========== FAILED ==========");
        return;
    }

    LogFile test1("/test1.txt");
    LogFile test2("test2.txt");

    test1.log("Hello\n");
    test1.log("W O R L D");

    test2.log("f\no\no");

    test1.log(" ?");

    SDC::makedir("/foodir");

    std::vector<String> list = SDC::listFiles("/");
    Serial.println("FILE LIST IN \"ROOT\":");
    for (String &s : list)
    {
        Serial.println(s);
    }

    LogFile test3("/foodir/aaa.txt");

    list = SDC::listFiles("/foodir");
    Serial.println("FILE LIST IN \"FOODIR\":");
    for (String &s : list)
    {
        Serial.println(s);
    }
}

void loop()
{
}
