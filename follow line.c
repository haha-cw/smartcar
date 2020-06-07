#include <STC89C5xRC.H>
#define uint unsigned int

sbit correct_right=P0^4;
sbit correct_left=P0^7;
sbit follow_right=P0^5;
sbit follow_left=P0^6;
bit follow_low;
extern uint mode_flag;
uint xj_distance;
void Timer0_Init();
void Delay1ms(unsigned int k);
void back();
void stop();
void go();
void local_left();
void local_right();
void Timer1_Init();
int juli();
void sonic_start();
void follow_line()
{
   Timer0_Init();
   Timer1_Init();
   follow_low=1;
   while(mode_flag==3)
     {
        sonic_start();xj_distance=juli();
       while(xj_distance<=20)  
        { 
          stop();sonic_start();xj_distance=juli();
        }
       if(correct_right==1&&correct_left==0)  //右外
       {
          back();Delay1ms(15);local_right();Delay1ms(60);
       }
        /*if(follow_right==1&&follow_left==0)  //右内
       {
          local_right();Delay1ms(70); 
       } */
       else if(correct_left==1&&correct_right==0)  //左外
       {
          back();Delay1ms(15);local_left();Delay1ms(60);
       }
       /*else if(follow_left==1&&follow_right==0)  //左内
       {
          local_left();Delay1ms(70);
       } */
       else 
       {
          go();Delay1ms(70);//前进降速
       }
      }
     stop(); follow_low=0;
}
