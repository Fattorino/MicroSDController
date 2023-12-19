#include <Arduino.h>
#include <vector>
#include "ToroSDController.h"

int attempts = 0;

void setup()
{
	Serial.begin(9600);
	Serial.print("\n");
	while (!SDC::init() && attempts < 15)
		attempts++;

	if (!SDC::ready)
	{
		Serial.println("========== FAILED ==========");
		return;
	}

	LogFile test1("/test1.txt");
	LogFile test2("test2.txt");

	test1.log("ciao\n");
	test1.log("come stai");

	test2.log("ciao\n");

	test1.log("?");

	SDC::makedir("/direc");

	std::vector<String> list = SDC::listFiles("/");
	Serial.println("FILE LIST:");
	for (String &s : list)
	{
		Serial.println(s);
	}

	LogFile test3("/direc/aaa.txt");

	list = SDC::listFiles("/direc");
	Serial.println("FILE LIST 2:");
	for (String &s : list)
	{
		Serial.println(s);
	}
}

void loop()
{
}
