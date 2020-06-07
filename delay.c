void Delay1ms(unsigned int k)		//@11.0592MHz
{
  while(--k)
 {	
    unsigned char i, j;
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
 }
}

void Delay20us()		//@11.0592MHz
{
	unsigned char i;

	i = 6;
	while (--i);
}