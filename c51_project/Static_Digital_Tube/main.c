#include <REGX52.H>
//###########################################################
//##
//##                         把数码管的值编成数组
//##
//###########################################################
//可以将数码管的显示图案对应的十六进制数
//编成一个数组来方便地控制其显示
unsigned char NixieTable[] = {
    0x3f, // 0 
    0x06, // 1 
    0x5b, // 2
    0x4f, // 3
    0x66, // 4
    0x6d, // 5
    0x7d, // 6
    0x07, // 7
    0x7f, // 8
    0x6f, // 9
    0x77, // A
    0x7c, // b
    0x39, // C
    0x5e, // d
    0x79, // E
    0x71, // F
    0x00, // 空
};




void NixieTube(unsigned char Location, unsigned char Number){
    //注意了，C语言的函数没有默认值，C++才有
    
    switch (Location){//用switch循环设置公共端，来选定数码管的哪一位亮
        case 1:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 1;
        
            break;
        case 2:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 0;
            
            break;

        case 3:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 1;
            
            break;

        case 4:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 0;
            
            break;

        case 5:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 1;
            
            break;

        case 6:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 0;
            
            break;
        
        case 7:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 1;
            
            break;

        case 8:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 0;
            
            break;
    }

    //把数码管那一位的显示图案对应的16进制数编成一个数组来方便的控制
    P0 =NixieTable[Number];
}


void main(void)
{
    NixieTube(1, 2);
    
    while (1){
    }
   
}