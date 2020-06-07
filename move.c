#include <STC89C5xRC.H>
#define uint unsigned int

sbit ENA=P3^6;  //左轮PWM调速
sbit ENB=P3^7;  //右轮PWM调速
sbit IN1=P1^4;
sbit IN2=P1^5;
sbit IN3=P1^6;
sbit IN4=P1^7;  //IN1,IN2左轮，IN3，IN4右轮
sbit SG_PWM=P2^4; //舵机PWM调速
extern bit follow_low;
extern bit obstacle_low;
uint PWM_count_EN;
extern PWM_count_sg;
extern uint mode_flag;
uint count_EN=0,count_sg=0;
uint a=0;


void Timer0_Init()
{
  TMOD &= 0xF0;		//设置定时器模式
  TMOD |= 0x01;		//设置定时器模式，T0定时方式1
  TH0=0xFF;
  TL0=0xA4;       //计数初值设置为0.1ms
  ET0=1;          //打开定时器0的中断
  EA=1;           //开总中断
  TR0=0;
}
void Timer0() interrupt 1     //左右轮PWM定时器
{  
   TH0=0xFF;
   TL0=0xA4;              
  if(count_EN<=PWM_count_EN)
  {
    ENA=1;ENB=1;
  }
  else
  {
    ENA=0;ENB=0;
  }
  count_EN++;
  if(count_EN>=200)
  {
    count_EN=0;
  }

}
void Timer2_Init()   
{
    T2MOD =0;		//初始化模式寄存器
	T2CON =0;		//初始化控制寄存器
	TL2 = 0xA4;		//设置定时初值
	TH2 = 0xFF;		//设置定时初值
	RCAP2L = 0xA4;		//设置定时重载值
	RCAP2H = 0xFF;		//设置定时重载值
    EA=1;
    TR2=0;
    ET2=1;        //开定时器2中断
}
void Timer2() interrupt 5      //舵机PWM调角
{ 
   TF2=0;
   TR2=0;
   TL2 = 0xA4;		
   TH2 = 0xFF;                
  if(count_sg<=PWM_count_sg)
  {
      SG_PWM=1;
  }
  else
  {
      SG_PWM=0;
  }
  count_sg++;
  if(count_sg>=200)
  {
    count_sg=0;
    a++;
  }
  TR2=1;
}
void PWM_EN(uint k)
{
  PWM_count_EN=k;
}
void PWM_sg(uint k)
{
  PWM_count_sg=k;
}
void stop()
{
   TR0=0;
   IN1=0;
   IN2=0;
   IN3=0;
   IN4=0;
   
}
void go()
{
  if(obstacle_low) PWM_EN(85);  //避障降速或降速循迹
  else if(follow_low) PWM_EN(40);
  else  PWM_EN(150);
   TH0=0xFF;
   TL0=0xA4;
   TR0=1;  
   IN1=0;
   IN2=1;
   IN3=0;
   IN4=1;
}

void back()
{
   PWM_EN(150);
   TH0=0xFF;
   TL0=0xA4;
   TR0=1;
   IN1=1;
   IN2=0;
   IN3=1;
   IN4=0;
}

void local_left()
{
   PWM_EN(100);
   TH0=0xFF;
   TL0=0xA4;
   TR0=1;
   IN1=1;
   IN2=0;
   IN3=0;
   IN4=1;
   
}

void local_right()
{
   PWM_EN(100);
   TH0=0xFF;
   TL0=0xA4;
   TR0=1;
   IN1=0;
   IN2=1;
   IN3=1;
   IN4=0; 
}




