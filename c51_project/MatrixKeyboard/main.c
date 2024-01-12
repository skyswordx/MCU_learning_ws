#include <REG52.H>
#include "Delay1ms.h"
#include "LCD1602.h"
#include "MatrixKeyboard.h"

unsigned char Key_value;


void main(){
    LCD_Init();
    LCD_ShowString(1,1,"Matrix Keyboard");
    while(1){
        Key_value = MatrixKeyboardScan();
        //用Key_value来接住返回值，如果返回值不为0，就显示出来
        if(Key_value != 0){
            LCD_ShowNum(2,1,Key_value,2);
            //显示在第二行第一列，范围是显示两位数
        }
    }

}