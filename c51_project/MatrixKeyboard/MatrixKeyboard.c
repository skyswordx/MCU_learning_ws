#include <REGX52.H>
#include "Delay1ms.h"

/**
  * @brief  矩阵键盘扫描函数
  * @param  None
  * @retval key_value 返回按下键的值
  * 如果按键按下不放，程序会停留在此函数中
  * 直到按键松开一瞬间，才会返回按键值
  * 没有按键按下时，返回值为0
  */
unsigned char MatrixKeyboardScan(void){

    unsigned char key_value = 0;
    //用来接住返回值，如果没有按下按键，返回值就为0

    P1 = 0xff;
    //先将所有列的位和行的位都拉高，这样就不会有短路的问题
    //这里采取按列扫描的方法，每一次拉低一个列的值，然后读取行的值
    
    P1_3 = 0;//拉低第一列，然后判断每一行的值并读取
    if(P1_7 == 0){
        Delay1ms(20);
        while(P1_7 == 0);
        Delay1ms(20);
        key_value = 1;
    }
    if(P1_6 == 0){
        Delay1ms(20);
        while(P1_6 == 0);
        Delay1ms(20);
        key_value = 5;
    }
    if(P1_5 == 0){
        Delay1ms(20);
        while(P1_5 == 0);
        Delay1ms(20);
        key_value = 9;
    }
    if(P1_4 == 0){
        Delay1ms(20);
        while(P1_4 == 0);
        Delay1ms(20);
        key_value = 13;
    }

    P1_2 = 0;//拉低第二列，然后判断每一行的值并读取
    if(P1_7 == 0){
        Delay1ms(20);
        while(P1_7 == 0);
        Delay1ms(20);
        key_value = 2;
    }
    if(P1_6 == 0){
        Delay1ms(20);
        while(P1_6 == 0);
        Delay1ms(20);
        key_value = 6;
    }
    if(P1_5 == 0){
        Delay1ms(20);
        while(P1_5 == 0);
        Delay1ms(20);
        key_value = 10;
    }
    if(P1_4 == 0){
        Delay1ms(20);
        while(P1_4 == 0);
        Delay1ms(20);
        key_value = 14;
    }

    P1_1 = 0;//拉低第三列，然后判断每一行的值并读取
    if(P1_7 == 0){
        Delay1ms(20);
        while(P1_7 == 0);
        Delay1ms(20);
        key_value = 3;
    }
    if(P1_6 == 0){
        Delay1ms(20);
        while(P1_6 == 0);
        Delay1ms(20);
        key_value = 7;
    }
    if(P1_5 == 0){
        Delay1ms(20);
        while(P1_5 == 0);
        Delay1ms(20);
        key_value = 11;
    }
    if(P1_4 == 0){
        Delay1ms(20);
        while(P1_4 == 0);
        Delay1ms(20);
        key_value = 15;
    }

    P1_0 = 0;//拉低第四列，然后判断每一行的值并读取
    if(P1_7 == 0){
        Delay1ms(20);
        while(P1_7 == 0);
        Delay1ms(20);
        key_value = 4;
    }
    if(P1_6 == 0){
        Delay1ms(20);
        while(P1_6 == 0);
        Delay1ms(20);
        key_value = 8;
    }
    if(P1_5 == 0){
        Delay1ms(20);
        while(P1_5 == 0);
        Delay1ms(20);
        key_value = 12;
    }
    if(P1_4 == 0){
        Delay1ms(20);
        while(P1_4 == 0);
        Delay1ms(20);
        key_value = 16;
    }
    
    return key_value;//千万不要忘记写返回值
}