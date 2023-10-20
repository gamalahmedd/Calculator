#include <avr/io.h>
#include "MACROS.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "DIO.h"
#include "Timer.h"
#include "Motor.h"

int main(void)
{
	unsigned char duty_cycle = 100;
	unsigned char read_value = 0;
	unsigned char digit_one = 0;
	unsigned char digit_two = 0;
	unsigned char flag = 0;
	Motor_vInit('D');
	LCD_vInit();
	KEYPAD_vInit('C');
	Timer_vInitPhaseCorrectMode(duty_cycle);
    while(1)
    {
		while(flag == 0)
		{
			LCD_vClearScreen();
			LCD_vSendString("Please Turn Motor On");
			do 
			{
				read_value = KEYPAD_u8Read('C');
			} while (read_value == NOTPRESSED);
			if(read_value == 'A')
			{
				Motor_vDirectionClockwise('D');
				flag = 1;
			}
		}
		LCD_vClearScreen();
		LCD_vSendString("1: Reset Speed");
		LCD_vMoveCursor(1, 20);
		LCD_vSendString("2: Change Direction");
		LCD_vMoveCursor(2, 1);
		LCD_vSendString("3: Turn Off Motor");
		while(flag == 1)
		{
			do 
			{
				read_value = KEYPAD_u8Read('C');
			} while (read_value == NOTPRESSED);
			if(read_value == '1')
			{
				LCD_vClearScreen();
				LCD_vSendString("Please Enter Duty Cycle:");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("Range 0 - 99");
				LCD_vMoveCursor(1, 25);
				duty_cycle = 0;
				do
				{
					read_value = KEYPAD_u8Read('C');
				} while (read_value == NOTPRESSED);
				LCD_vSendChar(read_value);
				digit_one = (read_value - 48);
				do
				{
					read_value = KEYPAD_u8Read('C');
				} while (read_value == NOTPRESSED);
				if(read_value == '=')
				{
					duty_cycle = digit_one;
				}
				else
				{
					LCD_vSendChar(read_value);
					digit_two = (read_value - 48);
					do
					{
						read_value = KEYPAD_u8Read('C');
					} while (read_value != '=');
					duty_cycle = (digit_one * 10) + digit_two;
				}
				Timer_vInitPhaseCorrectMode(duty_cycle);
				LCD_vClearScreen();
				LCD_vSendString("1: Reset Speed");
				LCD_vMoveCursor(1, 20);
				LCD_vSendString("2: Change Direction");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("3: Turn Off Motor");
			}
			else if(read_value == '2')
			{
				Motor_vTurnOff('D');
				LCD_vClearScreen();
				LCD_vSendString("Set Dircetion Of Motor");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("0-Clockwise 1-Anti-Clockwise");
				do
				{
					read_value = KEYPAD_u8Read('C');
					if(read_value == '0')
					{
						break;
					}
					if(read_value == '1')
					{
						break;
					}
				} while (1);
				if(read_value == '0')
				{
					Motor_vDirectionClockwise('D');
				}
				else
				{
					Motor_vDircetionAntiClock('D');
				}
				LCD_vClearScreen();
				LCD_vSendString("1: Reset Speed");
				LCD_vMoveCursor(1, 20);
				LCD_vSendString("2: Change Direction");
				LCD_vMoveCursor(2, 1);
				LCD_vSendString("3: Turn Off Motor");
			}
			else if(read_value == '3')
			{
				Motor_vTurnOff('D');
				flag = 0;
			}
		}		
    }
}