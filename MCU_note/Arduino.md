# 遇到的问题和解决资料
问题
	[avrdude: ser_open(): can‘t open device “\\.\COM以及串口监视器没反应](https://blog.csdn.net/qq_48637874/article/details/119658786)

手册
1. [df编程参考手册](https://wiki.dfrobot.com.cn/Arduino%E7%BC%96%E7%A8%8B%E5%8F%82%E8%80%83%E6%89%8B%E5%86%8C)
2. [arduino官方编程手册](https://www.arduino.cc/reference/en/)

论坛
1. [Arduino中文论坛, DF创客社区 (dfrobot.com.cn)](https://mc.dfrobot.com.cn/forum-92-1.html)
2. [Arduino - 极客工坊 - Powered by Discuz! (geek-workshop.com)](https://www.geek-workshop.com/forum-49-1.html)

教程
1. [df](https://mc.dfrobot.com.cn/featured/arduino)
2. [资源](https://mc.dfrobot.com.cn/thread-1249-1-1.html)

小车配件
1. [1838红外遥控](https://blog.csdn.net/qq_17351161/article/details/107437382?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22107437382%22%2C%22source%22%3A%222301_79069845%22%7D&fromshare=blogdetail&shareId=35&sharetype=hot)
2. [超声波测距](http://t.csdnimg.cn/QQBmo)
3. [SG90舵机](http://t.csdnimg.cn/TFwCG)
4. [循迹](http://t.csdnimg.cn/421qY)
5. [uno资料](https://blog.csdn.net/m0_37738838/article/details/85045066)
6. 


# 跟教程做笔记系列
## 1

在Arduino中，引脚就是io口，也就对应着某一寄存器的位，利用10进制表示
对于uno主板，数字引脚是0~13（一般不用前面的引脚，因为会有占用）

Arduino程序必须包含setup()和loop()两个函数，否则不能正常工作

在Arduino中程序运行时将首先调用 setup() 函数，每次 Arduino 上电或重启后，setup 函数只运行一次，可以在里面初始化变量和引脚模式，开始使用某个库，等等
```cpp
void setup(){
	/*
		1.设置引脚模式（利用pinMode()设定某一引脚的模式
			void setup(){
				pinMode(LED_pin, OUTPUT);
			}
			
		2.初始化变量（如果某一引脚是OUTPUT利用digitalWrite()写入）
			void setup(){
				pinMode(LED_pin, OUTPUT);
				digitalWrite(LED_pin,HIGH);
			}

		3.使用某个库
	*/
}
```

设置引脚模式使用pinMode()函数，它可以配置引脚为输出OUTPUT或输入INPUT模式
```cpp
void pinMode (uint8_t pin, uint8_t mode)
	  /*
		  参数:
		  pin 引脚编号
		  mode: INPUT, OUTPUT, 或 INPUT_PULLUP
		  
		  理解:
			  INPUT是输入的信号，是外部给控制器的信号，根据外部环境变化才给到控制器信号
				  比如像我们之后会用到的按钮，它就是典型的INPUT模式
				  它需要我们按下按键后，控制器才能接收到外部给它的指令

			  OUTPUT是输出信号，你需要让控制器能反应出某些特征，向外界发出信号
				  典型的就是LED，它闪烁的过程就是向外部发出信号的过程
				  又比如我们后面会用到的蜂鸣器，一个会发出声音的玩意儿
				  发声的过程就是向外界发出信号的过程，所以它也是OUTPUT

		  注解:
			  模拟引脚也可以当作数字引脚使用, 编号为14(对应模拟引脚0)到19(对应模拟引脚5).
	  */
```

把高电平低电平写入引脚使用digitalWrite()函数，注意在写引脚之前，需要将引脚设置为OUTPUT模式
```cpp
void digitalWrite (uint8_t pin, uint8_t value)
		/*
			参数:
				pin 引脚编号
				value HIGH 或 LOW
		
			理解：
				这个函数的意义是:引脚pin在pinMode()的中被设置为OUTPUT模式时,其电压将被设置为相应的值
				HIGH为5V(3.3V控制板上为 3.3V)，LOW为0V
				
			注解:
				对于uno，模拟引脚也可以当作数字引脚使用, 编号为14(对应模拟引脚0)到19(对应模拟引脚5)
		*/
```
读取某一引脚是高电平还是低电平使用digitalRead()函数，注意在读引脚之前，需要将引脚设置为INPUT模式
```cpp
void digitalRead(uint8_t pin)
```


pinMode()中的INPUT与OUTPUT设置是有讲究的，是由元件上的信号是从外界流向控制器Arduino还是从arduino流向外界相关的
1. 信号从控制器Arduino流向外界，引脚pin要被设置为OUTPUT
2. 信号从外界流向Arduino，引脚pin要被设置为INPUT
而在pinMode()里面设置INPUT和OUTPUT与之后程序需要如何执行也有着紧密关系的。
1. 既然pin是OUTPUT的话，那势必是控制器Arduino要给外界信号，所以需要Arduino给引脚先写入信号——digitalWrite()，才能把引脚的信号给到外界
2. 如果pin是INPUT的话，是外界给了控制器Arduino信号，所以需要Arduino读取引脚信号——digitalRead()，才能把外界的信息读取到控制器Arduino

下表是一张对应表

|比如:LED、蜂鸣器|比如:按键控制|
|---|---|
|pinMode(pin,OUTPUT)|pinMode(pin,INPUT)|
|digitalWrite(pin,HIGH/LOW)|digitalRead(pin)|

loop()函数是Arduino程序的main部分，在 setup() 函数中设置引脚给初始化变量后，就开始执行 loop() 函数。顾名思义，该函数在程序运行过程中不断的循环，loop()函数中的每条语句都逐次进行，直到函数的最后，然后再从loop函数的第一条语句再次开始。一直这样循环下去，直到关闭Arduino或者按下重启按钮

delay()函数让Arduino程序等待一段时间，参数是整数，单位是毫秒(1秒有1000毫秒)
```cpp
void delay (unsigned long ms)
	/*
		警告: 
			int整型变量只能存储一个-32768~到2767之间的整数
			对于存储时间最大可以存储32秒（32768毫秒约为32秒）
			
			long类型可以存放一个-2147483648到2147483647之间的整数
			
			unsigned long类型，则不存储负数
			所以存储的范围就从0到4294967295（时间可达49天）

			
		注解：
			因此输入参数时，注意参数的类型
			
			直接输入数字默认是int类型
			因此在延时参数超过32767(int型最大值)时
			需要用"UL"后缀表示为无符号长整型
				例如: delay(60000UL);
		
			同样输入表达式作为参数, 表达式中有int类型时, 需要强制转换为 unsigned long类型
				例如：
				int time =32000
				delay((unsigned long)time * 100UL);
	*/	
```

|数据类型|RAM|范围|
|---|---|---|
|boolean (布尔型)|1 byte|0 ~ 1（True 或False）|
|char（字符型）|1 byte|-128 ~ 127|
|unsigned char（无符号字符型）|1 byte|0~255|
|int（整型）|2 byte|-32768 ~ 32768|
|unsigned int（整型）|2 byte|0 ~ 65535|
|long（长整型）|4 byte|-2147483648 ~ 2147483647|
|unsigned long（无符号长整型）|4 byte|0 ~ 4294967295|
|boolean (布尔型)|1 byte|0 ~ 1（True 或False）|
|float（单精度浮点型）|4 byte|-3.4028235E38 ~ 3.4028235E38|
|double（单精度浮点型）|4 byte|-3.4028235E38 ~ 3.4028235E38|

**millis()是一个函数，该函数是Arduino语言自有的函数，它返回值是一个时间，Arduino开始运行到执行到当前的时间，也称之为机器时间，就像一个隐形时钟，从控制器开始运行的那一刻起开始计时，以毫秒为单位**，它常常可以和某一个引脚配合，获取该引脚变化过程的时间
```cpp
unsign long change_time; //用作暂时变量，存储引脚刚开始变化的时间
unsign long delta_time; //用来存储引脚变化过程的时间
change_time = millis(); //初次获取时间

...

delta_time = mills() - change_time; //引脚变化过程时间=引脚变化到当前时间-引脚初次变化时间
```


io口，或者说数字引脚，一般都是数字的（只有0或1，高电平和低电平两种状态）
把一个模拟值写入到一个引脚就要用到analogWrite()函数，使用这个函数是要具备特定条件的：引脚需具有PWM功能
**analogWrite()函数用于给PWM口写入一个0~255的模拟值
特别注意的是，analogWrite()函数只能写入具有PWM功能的数字引脚**
```cpp
void analogWrite(uint8_t analog_pin, int value)
```
观察一下Arduino板，查看数字引脚，你会发现其中6个引脚（3、5、6、9、10、11）旁标有“~”，这些引脚不同于其他引脚，因为它们可以输出PWM信号

**PWM是一项通过数字方法来获得模拟量的技术**，数字电信号的高低电平可以形成一个方波，所以方波信号只有开关两种状态。但是通过控制开与关所持续时间的比值就能模拟到一个0到5V之间变化的电压。
开（学术上称为高电平）所占用的时间就叫做脉冲宽度，所以PWM也叫做脉冲宽度调制
[[PWM理解]]

## 2
基本的流程
1. 画出电路图
2. 为元件选择引脚
3. 组装电路

1. 为引脚声明整型变量，用变量名字表示引脚
2. 设置setup()，选择输出/输入模式
3. 编写loop()逻辑，实现电路功能


LED_blinking
```cpp
int ledPin = 13;   // LED connected to digital pin 13
/*
	给LED灯所在的引脚13起个响亮的名字，叫"LED"，注意，引脚用整型数字表示，所以变量是整型的
	需要注意的是：UNO板上的"L"灯已经和数字引脚13相连了，所以也就是为什么声明为“13”的原因
*/

//在这个程序里有两个函数，一个叫做setup，它的主要目的是在loop函数运行之前为程序做必要的设置
//Arduino程序必须包含setup()和loop()两个函数，否则不能正常工作

void setup() // initialize the digital pin as an output.
{
	/*
		在Arduino中程序运行时将首先调用 setup() 函数
		每次 Arduino 上电或重启后，setup 函数只运行一次
		可以在里面初始化变量和引脚模式，开始使用某个库，等等
			1.设置引脚模式（利用pinMode()设定某一引脚的模式
			2.初始化变量（如果某一引脚是OUTPUT利用digitalWrite()写入）
			3.使用某个库
			
		这里只是初始化数字引脚为OUTPUT模式
	*/

    pinMode(ledPin, OUTPUT);    // sets the digital pin as output
    /*
	  void pinMode (uint8_t pin, uint8_t mode)
	  用于设置引脚模式，配置引脚为输出或输出模式

	  参数:
		  pin 引脚编号
		  mode: INPUT, OUTPUT, 或 INPUT_PULLUP
		  
	  理解:
		  INPUT是输入的信号，是外部给控制器的信号，根据外部环境变化才给到控制器信号
			  比如像我们之后会用到的按钮，它就是典型的INPUT模式
			  它需要我们按下按键后，控制器才能接收到外部给它的指令

		  OUTPUT是输出信号，你需要让控制器能反应出某些特征，向外界发出信号
			  典型的就是LED，它闪烁的过程就是向外部发出信号的过程
			  又比如我们后面会用到的蜂鸣器，一个会发出声音的玩意儿
			  发声的过程就是向外界发出信号的过程，所以它也是OUTPUT

	  注解:
		  模拟引脚也可以当作数字引脚使用, 编号为14(对应模拟引脚0)到19(对应模拟引脚5)
	*/
}

void loop()
{
	/*
	在 setup() 函数中初始化和定义了变量后，就开始执行 loop() 函数
	顾名思义，该函数在程序运行过程中不断的循环
	loop()函数中的每条语句都逐次进行，直到函数的最后，然后再从loop函数的第一条语句再次开始
	三次、四次……一直这样循环下去，直到关闭Arduino或者按下重启按钮
	*/

    digitalWrite(ledPin, HIGH);   // sets the LED on
    /*
	    给引脚13一个高电，让LED点亮
		
		void digitalWrite (uint8_t pin, uint8_t value)
		写入数字引脚，设置对应引脚的高低电平. 在写引脚之前, 需要将引脚设置为OUTPUT模式.

		参数:
			pin 引脚编号
			value HIGH 或 LOW
		
		理解：
			这个函数的意义是:引脚pin在 pinMode()的中被设置为OUTPUT模式时，其电压将被设置为相应的值
			HIGH为5V(3.3V控制板上为 3.3V)，LOW为0V
				这里就是给引脚10(ledPin)一个5V的高电平，点亮了引脚10这个LED

		注解:
			对于uno，模拟引脚也可以当作数字引脚使用, 编号为14(对应模拟引脚0)到19(对应模拟引脚5).
		
    */
    
    delay(1000);                  // waits for a second
	/*
		void delay (unsigned long ms)
		让arduino延时, 单位是毫秒(1秒有1000毫秒).

		警告: 
		参数为unsigned long, 因此在延时参数超过32767(int型最大值)时,
		需要用"UL"后缀表示为无符号 长整型, 例如: delay(60000UL);
		
		同样在参数表达式, 切表达式中有int类型时, 需要强制转换为 unsigned long类型,
		例如: delay((unsigned long)tdelay * 100UL);

	*/

    digitalWrite(ledPin, LOW);    // sets the LED off
    delay(1000);                  // waits for a second
}
```


# 做项目积累的tips
3个传感器就是长度为3的数组
然后取值只有0或1

可以把它编码成2进制的数
0-1-0是直行，相当于二进制010=十进制2

然后就可以把{0或1，0或1，0或1}这样的数组总共8种可能都对应一个整数

遇事不决后退一下

问题在于那根线会到两个传感器中间，导致出现倒退，然后再前进，反复横跳。昨天没问题是因为供电不足

传感器的问题是密度，如果传感器密度不够的话就是离散的，没办法使用默认为连续传感器的算法精细判断，得研究现象推断原因

电源模块要搞定

绑住万向轮增加阻尼系数

录视频来分析运行情况，进行debug

# 红外模块
[[1838红外接收器的结构.excalidraw]]

[Arduino测试IRremote红外接收信号（同一按钮，多个结果）问题解决_arduino irremote_eamonwu68的博客-CSDN博客](https://blog.csdn.net/eamonwu68/article/details/129867813)

1.包含头文件（注意版本号，我用到是2.80可以正常接收）
2.准备变量
	1.需要给红外接收器1838的out输出端设定一个引脚（recv代表receive）
	2.然后把该引脚用作参数，利用构造函数初始化一个红外接受信号的对象，类型为IRrecv
	3.创建一个红外转电信号的解码对象，用来储存接收到并解码的红外信息，类型为decode_results
3.设置setup函数
	1.使用Serial.begin(9600)打开串口监视器端口9600
	2.利用IRrecv类型的接收对象的成员函数enableIRIn()启动红外接收
4.在loop函数实现逻辑
	1.利用IRrecv类型的接收对象的成员函数decode()解码，注意其参数是类型为decode_results的解码对象的地址
	2.使用if语句判断是否解码成功，就利用上面那条语句作为条件判断：decode()函数用于判断红外接收器所接收到的红外信号是否可以被解析，如果可以成功解析，则返回非零数值。并将解析结果存储于类型为decode_results的解码对象中；如果无法成功解析，则返回零。
	3.类型为decode_results的解码对象的属性value就是解码后的二进制数字信息，可以使用if语句和一个十六进制数判断红外信号是否是来自于特定按键
	4.利用IRrecv类型的接收对象的成员函数resume()恢复接收下一个红外信号

```cpp
//##############包含头文件件###########
#include <IRremote.h>
//##############准备变量###############
//1.需要给红外接收器1838的out输出端设定一个引脚
int RECV_PIN = 11;

//2.然后把该引脚用作参数，利用构造函数初始化一个红外接受信号的对象
IRrecv irrecv(RECV_PIN); 

//3.创建一个红外转电信号的解码对象，用来储存接收到的红外信息
decode_results decode_results;

//##############设置setup函数###########
void setup(){
	//1.打开串口监视器端口9600
	Serial.begin(9600); 
	//2.启动红外接收
	Serial.println("Enabling IRin");//提示
	irrecv.enableIRIn();
	Serial.println("Enabled IRin");//提示
}
```





# 超声波模块
[舵机控制](https://arduino.nxez.com/2016/12/20/use-arduino-to-control-the-steering-gear.html)
[超声波避障](https://ost.51cto.com/posts/787)
超声波模块一般装在有伺服舵机的云台上面

首先了解伺服舵机和超声波模块![[HC-SR04超声波模块.excalidraw]]

1.包含伺服舵机头文件Sevro.h
2.准备变量
	1.创建Servo类型的舵机对象
	2.定义超声波模块的向外发送超声波信号的triger引脚
	3.定义接收反射回来的超声波的echo引脚
3.设置setup函数
	1.使用Serial.begin(9600)打开串口监视器端口9600
	2.利用Servo类型的舵机对象的attach()成员函数实现舵机引脚的初始化，注意参数是具有PWM功能的引脚
	3.使用pinMode()设置超声波引脚的模式
		1.triger引脚设置为OUTPUT，因为Arduino主板向triger引脚发送电信号，再通过超声波模块转换成超声波
		2.echo引脚设置为INPUT，因为超声波模块接收到反射信号后，用echo引脚向Arduino主板传回二进制信号，Arduino主板需要读取echo引脚
4.设置实现逻辑
	2.
		1.设置一个int类型的中间变量postion(取值范围是0~255)，用来表示伺服舵机的偏离角
		2.设置一个多维数组`distances[n]`，用来存储n个方向的超声波测算结果
		3.利用Servo类型的舵机对象的write()成员函数实现舵机的角度控制，参数是前面设置的position中间变量，并注意延时一段时间
	1.根据超声波间隔的时间计算获得小车和障碍物的距离
		1.使发出发出超声波信号的triger引脚
			1.先低电平2μs，注意延迟微妙使用delayMicroseconds();
			2.高电平至少10μs
			3.恢复发出超声波信号的triger引脚为低电平





	








# L289N驱动摸块
[L289N](https://blog.csdn.net/weixin_44751294/article/details/110503256)

