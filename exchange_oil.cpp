/*有一个装满油的10升的桶，一个3升的空桶，一个7升的空桶，
如何把油平均成5升*/

#include <stdio.h>
typedef struct _proess{
	int i_map[1000][2];
	int seat;
}s_proess_;
/*判断此状态是否存在*/
bool ergodic(s_proess_ *s_proess, int fornt)
{
	for(int i = 0; i < s_proess->seat; i++)
	{
		if(s_proess->i_map[i][0] == fornt)
		{
			return true;
		}
	}
	return false;
}
/*get出前一个状态*/
int get(s_proess_ *s_proess, int v)
{
	for(int i = 0; i < s_proess->seat; i++)
	{
		if(s_proess->i_map[i][0] == v)
		{
			return s_proess->i_map[i][1];
		}
	}
	return 0;
}
int handl(s_proess_ *s_proess, int b10, int b3, int b7, int fornt)
{
	int v = 0;
	v = (b10<<8) + (b3<<4) + b7;
	/*如果此状态存在直接返回*/
	if(ergodic(s_proess, v))
		return 0;
	
	s_proess->i_map[s_proess->seat][0] = v;
	s_proess->i_map[s_proess->seat][1] = fornt;
	s_proess->seat++;
	if(5 == b10 || 5 == b7)
	{
		int key = v;
		while(1)
		{
			printf("%d  %d  %d\n", (key&0xF00)>>8, (key&0xF0)>>4, (key&0xF));
			if(0 == (key = get(s_proess, key)))
			{
				break;
			}
		}
		static int times = 0;
		printf("-----------------------%d\n", ++times);
	}
	return 0;
}
int main(int argc, char*argv[])
{
	s_proess_ s_proess = {0};
	s_proess.i_map[0][0] = 0xA00;
	s_proess.i_map[0][1] = 0;
	s_proess.seat = 1;

	int b10 = 0;/*10升桶*/
	int b3 = 0;/*3升桶*/
	int b7 = 0;/*7升桶*/
	int k = 0;
	int i = 0;

	/*桶 10 桶 3 桶 7*/
	printf("%d  %d  %d\n", 10, 3, 7);
	printf("-----------------------\n");
	for(i = 0; i < s_proess.seat; i++)
	{
		k = s_proess.i_map[i][0];
		b10 = (k&0xF00)>>8;
		b3 = (k&0xF0)>>4;
		b7 = (k&0xF);

		/*此状态不需要再变化*/
		if(b10 == 5 || b7 == 5) continue;

		/*如果10桶里面不为空，就能往3或7桶里倒*/
		if(b10 != 0)
		{
			/*如果3桶里面不满，10桶就能往3桶里面倒*/
			if(b3 != 3)
			{
				/*如果10桶加3桶不能让3桶满，则10桶为0，否则10桶为倒满3桶后剩下的油*/
				handl(&s_proess, (b10+b3)>3?b10+b3-3:0, (b10+b3)>3?3:b10+b3, b7, k);
			}
			/*如果7桶里面不满，10桶就能往7桶里面倒*/
			if(b7 != 7)
			{	
				/*如果10桶加7桶不能让7桶满，则10桶为0，否则10桶为倒满7桶后剩下的油*/
				handl(&s_proess, (b10+b7)>7?b10+b7-7:0, b3, (b10+b7)>7?7:b10+b7, k);
			}
		}

		if(b3 != 0)
		{
			if(b10 != 10)
			{
				handl(&s_proess, (b10+b3)>10?10:b10+b3, (b10+b3)>10?b10+b3-10:0, b7, k);
			}
		
			if(b7 != 7)
			{	
				handl(&s_proess, b10, (b7+b3)>7?b7+b3-7:0, (b7+b3)>7?7:b7+b3, k);
			}
		}

		if(b7 != 0)
		{
			if(b10 != 10)
			{
				handl(&s_proess, (b10+b7)>10?10:b10+b7, b3, (b10+b7)>10?b10+b7-10:0, k);
			}
		
			if(b3 != 3)
			{	
				handl(&s_proess, b10, (b3+b7)>3?3:b3+b7, (b3+b7)>3?b7+b3-3:0, k);
			}
		}
	}
}
