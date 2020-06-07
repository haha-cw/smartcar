#include <STC89C5xRC.H>
#define uint unsigned int
void Delay1ms(unsigned int k);
void Delay20us();

uint time;
uint distance;
sbit trig=P0^0;
sbit echo=P0^1;
void sonic_start()
{
   trig=1;Delay20us();
   trig=0;
}

void Timer1_Init()
{
   EA=1;
   ET1=1;
   TH1=0;
   TL1=0;
   TMOD &= 0x0F;		//设置定时器模式
   TMOD |= 0x10;		//设置定时器模式
   TR1=0;
}
int juli()
{
   while(!echo);
    TR1=1;
   while(echo);
    TR1=0;
  time=TH1*256+TL1;
  distance=time*1.7/100; //cm(可行)，dm和mm都不可行
  TH1=0;TL1=0;    //计时完对计数器置0，免得下一次测量结果为上次和本次相加（很重要！）
  
  return distance;
}