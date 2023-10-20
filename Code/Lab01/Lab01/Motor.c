#include "DIO.h"
#include "MACROS.h"

void Motor_vInit(unsigned char portname)
{
	DIO_vsetPinDir(portname, PIN0, OUTPUT);
	DIO_vsetPinDir(portname, PIN1, OUTPUT);
}

void Motor_vDirectionClockwise(unsigned char portname)
{
	DIO_vWritePin(portname, PIN0, ENABLE);
	DIO_vWritePin(portname, PIN1, DISABLE);
}

void Motor_vDircetionAntiClock(unsigned char portname)
{
	DIO_vWritePin(portname, PIN0, DISABLE);
	DIO_vWritePin(portname, PIN1, ENABLE);
}

void Motor_vTurnOff(unsigned char portname)
{
	DIO_vWritePin(portname, PIN0, DISABLE);
	DIO_vWritePin(portname, PIN1, DISABLE);
}