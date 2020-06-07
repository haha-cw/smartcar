#include <STC89C5xRC.H>
#define uint unsigned int

void Timer0_Init();
void Delay1ms(unsigned int k);
void Timer1_Init();
void Timer2_Init();	
void sonic_start();
int juli();
void Steering_engine();
void back();
void stop();
void go();
void local_left();
void local_right();

uint PWM_count_sg=10;
extern uint mode_flag;
extern uint a; 
bit obstacle_low=0;
uint sonic_distance,distance_left,distance_right;

void Steering_engine()
{  
   while(1)
    {
      if(a==50)                         //50ʹ���ת��ָ���ǶȲ�ֹͣԼ1.5��
      {
         PWM_count_sg=3;  //�����������ƫ��50-100��,��������ǰλ
      }
      if(a==100)      
     {
         PWM_count_sg=16; //�����������ƫ��100-150������������λ
      TR2=0;sonic_start();distance_right=juli();a+=1;TR2=1;
      }
      if(a==150)
      {
         PWM_count_sg=10; //���������������0-50������������λ
         TR2=0;sonic_start();distance_left=juli();
         a=0;break;
      }
    }
}

void obstacle_avoidance_mode()
{
   Timer0_Init();
   Timer1_Init();
   Timer2_Init();
   obstacle_low=1;
   TR2=1;while(a<=50);TR2=0;a=0;  //��ʼ�������
  while(mode_flag==2)
   {  
     sonic_start();sonic_distance=juli();
     if(sonic_distance<=30)
     {
     stop();
     TR2=1;  //�򿪶��
     Steering_engine();
     TR2=1;while(a<=50);a=0;  //�����������
     TR2=0;   //�رն��
     if(distance_right>distance_left&&distance_right>30){
       local_right();Delay1ms(330);stop();}
     else if(distance_left>distance_right&&distance_left>30){
       local_left();Delay1ms(340);stop();}
     else{
       back();Delay1ms(260);local_right();Delay1ms(100);stop();}
     }
     else
      go();
    }
    obstacle_low=0;
}
