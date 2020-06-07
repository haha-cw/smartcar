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
    ES=1;     //�����жϺʹ����жϣ���Ҫ�Լ���ӣ����û������
    PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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
