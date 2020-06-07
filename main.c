#include <STC89C5xRC.H>
#define uchar unsigned char
#define uint unsigned int


void obstacle_avoidance_mode();
void blueteeth_mode();
void follow_line();
void key_int();

uint mode_flag=1;
void main()
{
  key_int();
 while(1)
 {
   if(mode_flag==1)
   {
     blueteeth_mode();
   }
   else if(mode_flag==2)
   {
     obstacle_avoidance_mode();
   }
   else if(mode_flag==3)
   {
      follow_line();
   }
 }
}

