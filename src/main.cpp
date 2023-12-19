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

	SDC::makedir("/direc");

	std::vector<String> list = SDC::listFiles("/");
	Serial.println("FILE LIST:");
	for (String &s : list)
	{
		Serial.println(s);
	}
}

void loop()
{
}
