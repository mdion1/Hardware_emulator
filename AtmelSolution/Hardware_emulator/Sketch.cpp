/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */
//Beginning of Auto generated function prototypes by Atmel Studio
uint64_t getNow();
//End of Auto generated function prototypes by Atmel Studio

static volatile int value = 1;

void FunctionToStop() {
	for(int i = 1; i < 100; ++i) {
		value *= i;
	}
	
	--value;
}

#include <Hardware_emulator_cpp/Hardware_emulator.cpp>