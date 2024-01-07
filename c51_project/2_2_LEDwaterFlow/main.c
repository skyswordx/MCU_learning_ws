#include <REGX52.H>
#include <INTRINS.H>
//##############################LED############################



void Delay1ms( unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;

	while(xms){
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do{
			while (--j);
		} while (--i);
		--xms;
	}
	
}
//利用写死的延迟1ms，传入参数进行给定次的循环，实现任意单位1ms的延迟函数

void LED_flood( unsigned int xms){
		P2 = 0xFE; //1111 1110
		Delay1ms(xms);	
	
		P2 = 0xFD; //1111 1101
		Delay1ms(xms);
		
		P2 = 0xFB; //1111 1011
		Delay1ms(xms);
		
		P2 = 0xF7; //1111 0111
		Delay1ms(xms);
		
		P2 = 0xEF; //1110 1111
		Delay1ms(xms);
		
		P2 = 0xDF; //1101 1111
		Delay1ms(xms);
		
		P2 = 0xBF; //1011 1111
		Delay1ms(xms);
		
		P2 = 0x7F; //0111 1111
		Delay1ms(xms);
}

//############################button###########################
void LED_button(){
	while(1){
		if (P3_1 == 0){
			Delay1ms(20); //等待20ms，进行按下过程的消抖
			while(P3_1);//写一个只要按键是按下状态就会运行的空循环，等待松手
			Delay1ms(20);//等待20ms，进行松开过程的消抖

			P2_0 = ~P2_0;
			
		}
	}
}

void LED_bit(){
	unsigned char LED_bit=0;//定义变量必须在前面
	P0 = 0x00;

	while (1){
		
		if(P3_1 == 0){
			Delay1ms(20); //等待20ms，进行按下过程的消抖
			while(P3_1);//写一个只要按键是按下状态就会运行的空循环，等待松手
			Delay1ms(20);//等待20ms，进行松开过程的消抖

			LED_bit++;

			P2 = ~LED_bit;
		}

	}
}


void LED_mv_bit(){
	unsigned char LED_mv_bit = 0;
	while(1){
		if(P3_1 == 0){
			Delay1ms(20);
			while (P3_1==0);
			Delay1ms(20);

			//0000 0001   <<0
			//0000 0010   <<1
			//1000 0000   <<7

			if(LED_mv_bit >=8){
				LED_mv_bit = 0;
			}

			P2 = ~(0x01<<LED_mv_bit);

			LED_mv_bit++;
		
		}	
	}	

}


void main(){
	unsigned char LED_mv_bit = 0;
	while(1){
		if(P3_1 == 0){
			Delay1ms(20);
			while (P3_1==0);
			Delay1ms(20);

			//0000 0001   <<0
			//0000 0010   <<1
			//1000 0000   <<7

			if(LED_mv_bit >=8){
				LED_mv_bit = 0;
			}

			P2 = ~(0x01<<LED_mv_bit);

			LED_mv_bit++;
		
		}	
	}		
	
	
}

