#include <STC89C5xRC.H>
#define uint unsigned int

void Delay1ms(unsigned int k);
extern uint mode_flag;
sbit key=P3^3;
sbit spk=P2^5;

void key_int()
{
  EA=1;
  EX1=1;
  IT1=1;
}

void beep(uint n)
{
 while(n)
 {
   spk=0;Delay1ms(500);
   spk=1;Delay1ms(500);
  n--;
 }
}

void key_mode() interrupt 2
{
  Delay1ms(10);
  if(~key)
  {
     mode_flag++;
    if(mode_flag==4) mode_flag=1;
     beep(mode_flag);
  }
}