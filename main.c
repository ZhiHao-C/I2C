#include <REGX52.H>
#include "LCD1602.h"
#include "delay.h"
#include "keycode.h"
#include "AT24C02.h"
#define unchar unsigned char
unsigned int n1;
unsigned int n2;
unchar Data;
unchar keynum;
unsigned int n;
void main()
{
	LCD_Init();
	LCD_ShowNum(1,1,n,5);
	while(1)
	{
		keynum=key();
		if(keynum==1)
		{
			n++;
			LCD_ShowNum(1,1,n,5);
		}
		else if(keynum==2)
		{
			n--;
			LCD_ShowNum(1,1,n,5);
		}
		else if(keynum==3)
		{
			AT24C02_writebyte(2,(n/256));//往24c02地址为2 的地方写入数据
			delay_ms(5);
			AT24C02_writebyte(1,(n%256));
			delay_ms(5);
			
			LCD_ShowString(2,3,"write OK");
			delay_ms(500);
			LCD_ShowString(2,3,"        ");
		}
		else if(keynum==4)
		{
			n1=AT24C02_readbyte(1);
			n2=AT24C02_readbyte(2);//在24c02地址为2 的地方读取数据
			n=(n1)+(n2<<8);
			LCD_ShowNum(1,1,n,5);
			LCD_ShowString(2,3,"read OK");
			delay_ms(500);
			LCD_ShowString(2,3,"        ");
		}
	}
}