#include <avr/io.h>
#include "KEYPAD.h"
#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>;

int main(void)
{
	LCD_vInit();
	KEYPAD_vInit('D');
	unsigned long value1, value2;
	unsigned read_value;
	unsigned char operation;
	unsigned long long result = 0;
	unsigned char counter;
    while(1)
    {
		counter = 0;
		value1 = 0;
		value2 = 0;
		read_value = NOTPRESSED;
		while(counter < 5 && read_value != 'A' && read_value != '=')
		{
			do 
			{
				read_value = KEYPAD_u8Read('D');
			} 
			while (read_value == NOTPRESSED);
			if(counter == 0)
			{
				LCD_vClearScreen();
			}
			if(read_value == '+' || read_value == '-' || read_value == '/' || read_value == '*')
			{
				operation = read_value;
				break;
			}
			LCD_vSendChar(read_value);
			value1 = (value1 * 10) + (read_value - 48);
			counter++;
		}	
		while(read_value != '+' && read_value != '-' && read_value != '/' && read_value != '*' && read_value != 'A' && read_value != '=')
		{
			read_value = KEYPAD_u8Read('D');
			operation = read_value;
		}		
		if(read_value != 'A' && read_value != '=')
		{
			LCD_vSendChar(read_value);
		}		
		counter = 0;
		while(read_value != '=' && read_value != 'A' && counter < 5)
		{
			do 
			{
				read_value = KEYPAD_u8Read('D');
			} 
			while (read_value == NOTPRESSED);
			if(read_value == '+' || read_value == '-' || read_value == '/' || read_value == '*')
			{
				LCD_vSendChar(read_value);
				value1 = 0;
				continue;
			}
			else if(read_value == 'A' || read_value == '=')
			{
				break;
			}
			LCD_vSendChar(read_value);
			value2 = (value2 * 10) + (read_value - 48);
			counter++;
		}		
		while(read_value != '=' && read_value != 'A')
		{
			read_value = KEYPAD_u8Read('D');
		}
		if (read_value == 'A')
		{
			LCD_vClearScreen();
		}
		if(read_value == '=')
		{
			if(value1 == 0 || value2 == 0)
			{
				LCD_vClearScreen();
				LCD_vSendString("Syntax	Error!");
				_delay_ms(1000);
				LCD_vClearScreen();
			}
			else
			{
				LCD_vSendChar('=');
				switch(operation)
				{
					case '+':
						result = value1 + value2;
						break;
					case '-':
						result = value1 - value2;
						break;
					case '*':
						result = (long long) value1 * value2;
						break;
					case '/':
						result = value1/value2;
						break;
				}
				if(result >= 1000000000 && result <= 10000000000)
				{
					LCD_vSendChar((result / 1000000000) + 48);
					LCD_vSendChar(((result % 1000000000) / 100000000) + 48);
					LCD_vSendChar((((result % 1000000000) % 100000000) / 10000000) + 48);
					LCD_vSendChar(((((result % 1000000000) % 100000000) % 10000000) / 1000000) + 48);
					LCD_vSendChar((((((result % 1000000000) % 100000000) % 10000000) % 1000000) / 100000) + 48);
					LCD_vSendChar(((((((result % 1000000000) % 100000000) % 10000000) % 1000000) % 100000) / 10000) + 48);
					LCD_vSendChar((((((((result % 1000000000) % 100000000) % 10000000) % 1000000) % 100000) % 10000) / 1000) + 48);
					LCD_vSendChar(((((((((result % 1000000000) % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) / 100) + 48);
					LCD_vSendChar((((((((((result % 1000000000) % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar((((((((((result % 1000000000) % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) % 10) + 48);
				}
				else if(result >= 100000000 && result <= 1000000000)
				{
					LCD_vSendChar((result / 100000000) + 48);
					LCD_vSendChar(((result % 100000000) / 10000000) + 48);
					LCD_vSendChar((((result % 100000000) % 10000000) / 1000000) + 48);
					LCD_vSendChar(((((result % 100000000) % 10000000) % 1000000) / 100000) + 48);
					LCD_vSendChar((((((result % 100000000) % 10000000) % 1000000) % 100000) / 10000) + 48);
					LCD_vSendChar(((((((result % 100000000) % 10000000) % 1000000) % 100000) % 10000) / 1000) + 48);
					LCD_vSendChar((((((((result % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) / 100) + 48);
					LCD_vSendChar(((((((((result % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar(((((((((result % 100000000) % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) % 10) + 48);
				} 
				else if(result >= 10000000 && result <= 100000000)
				{
					LCD_vSendChar((result / 10000000) + 48);
					LCD_vSendChar(((result % 10000000) / 1000000) + 48);
					LCD_vSendChar((((result % 10000000) % 1000000) / 100000) + 48);
					LCD_vSendChar(((((result % 10000000) % 1000000) % 100000) / 10000) + 48);
					LCD_vSendChar((((((result % 10000000) % 1000000) % 100000) % 10000) / 1000) + 48);
					LCD_vSendChar(((((((result % 10000000) % 1000000) % 100000) % 10000) % 1000) / 100) + 48);
					LCD_vSendChar((((((((result % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar((((((((result % 10000000) % 1000000) % 100000) % 10000) % 1000) % 100) % 10) + 48);
				}
				else if(result >= 1000000 && result < 10000000)
				{
					LCD_vSendChar((result / 1000000) + 48);
					LCD_vSendChar(((result % 1000000) / 100000) + 48);
					LCD_vSendChar((((result % 1000000) % 100000) / 10000) + 48);
					LCD_vSendChar(((((result % 1000000) % 100000) % 10000) / 1000) + 48);
					LCD_vSendChar((((((result % 1000000) % 100000) % 10000) % 1000) / 100) + 48);
					LCD_vSendChar(((((((result % 1000000) % 100000) % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar(((((((result % 1000000) % 100000) % 10000) % 1000) % 100) % 10) + 48);
				}
				else if(result >= 100000 && result < 1000000)
				{
					LCD_vSendChar((result / 100000) + 48);
					LCD_vSendChar(((result % 100000) / 10000) + 48);
					LCD_vSendChar((((result % 100000) % 10000) / 1000) + 48);
					LCD_vSendChar(((((result % 100000) % 10000) % 1000) / 100) + 48);
					LCD_vSendChar((((((result % 100000) % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar((((((result % 100000) % 10000) % 1000) % 100) % 10) + 48);
				}
				else if(result >= 10000 && result < 100000 )
				{                                   
					LCD_vSendChar((result / 10000) + 48);
					LCD_vSendChar(((result % 10000) / 1000) + 48);
					LCD_vSendChar((((result % 10000) % 1000) / 100) + 48);
					LCD_vSendChar(((((result % 10000) % 1000) % 100) / 10) + 48);
					LCD_vSendChar(((((result % 10000) % 1000) % 100) % 10) + 48);
				}	
				else if(result >= 1000 && result < 10000)
				{
					LCD_vSendChar((result / 1000) + 48);
					LCD_vSendChar(((result % 1000) / 100) + 48);
					LCD_vSendChar((((result % 1000) % 100) / 10) + 48);
					LCD_vSendChar((((result % 1000) % 100) % 10) + 48);
				}
				else if(result >= 100 && result < 1000)
				{
					LCD_vSendChar((result / 100) + 48);
					LCD_vSendChar(((result % 100) / 10) + 48);
					LCD_vSendChar(((result % 100) % 10) + 48);
				}					
				else if(result >= 10 && result < 100)
				{
					LCD_vSendChar((result / 10) + 48);
					LCD_vSendChar((result % 10) + 48);
				}
				else if(result >= 0 && result < 10)
				{
					LCD_vSendChar(result + 48);
				}
			}
		}			
    }
}