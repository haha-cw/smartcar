#include <STC89C5xRC.H>
#define uchar unsigned char
#define uint unsigned int
uchar receive_data='0';
extern uint mode_flag;
void Timer0_Init();
void UartInit();
void Delay1ms(unsigned int k);
void back();
void stop();
void go();
void local_left();
void local_right();

void UartInit()		//9600bps@11.0592MHz
{
	EA=1;
    ES=1;     //开总中断和串口中断，需要自己添加，软件没有生成
    PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}


void uart_inter() interrupt 4
{
   EA=0;
  if(RI)
  {
    RI=0;
    receive_data=SBUF;
  }
  EA=1;
}

void blueteeth_mode()
{
    UartInit();
    Timer0_Init();
   while(mode_flag==1)
   {
    switch(receive_data)
    {
    case'1': go();break;
    case'2': back();break;
    case'3': local_left();break;
    case'4': local_right();break;
    case'0': stop();break;
    }
   }
}
