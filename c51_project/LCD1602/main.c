#include <REGX52.H>
#include "LCD1602.h"
#include "Delay1ms.h"


void main(){
    LCD_Init();
    LCD_ShowString(1,1,"yy:");
	
    while(1){
		LCD_ShowString(2,1,"Hello World!");
		Delay1ms(1000);
		
		//显示完字符串后，需要清屏，否则会出现显示混乱
        //和数码管一样，LCD1602也是有持续显示的特性，所以需要清屏
		LCD_ShowString(2,1,"            ");
                   
        LCD_ShowString(2,1,"I am yy!");
        Delay1ms(1000);
	}
}