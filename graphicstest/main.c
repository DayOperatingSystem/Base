#include <stdio.h>
#include <sys/utsname.h>

#define setpos(a,b) printf("\x1B[%d;%dh", a, b)
#define setcolor(f,b) printf("\x1B[3%d;4%dm", 30+f, 40+b)
#define setforeground(f) printf("\x1B[%dm", 30+f)
#define setbackground(b) printf("\x1B[%dm", 40+b)
#define cls printf("\x1B[j")

void fill(int x, int y, int w, int h, char c, int color)
{
	setbackground(color);	
	setpos(x, y);

	for(int i = 0; i < h; i++)
	{
		setpos(x, y + i);

		for(int j = 0; j < w; j++)
			putchar(c);
	}
	
}

int main(int argc, char* argv[])
{
	int xdir = 1;
	int ydir = 1;

	int xpos = 0;
	int ypos = 0;

	const int width = 10;
	const int height = 5;

	cls;
	while(1)
		{
			// Clear rect
			fill(xpos, ypos, width, height, ' ', 0);

			if(xpos <= 0)
				xdir = 1;
			else if(xpos + width >= 80)
				xdir = -1;

			if(ypos <= 0)
				ydir = 1;
			else if(ypos + height >= 25)
				ydir = -1;

			xpos += xdir;
			ypos += ydir;

			// Draw new rect
			fill(xpos, ypos, width, height, ' ', 1);
			fflush(stdout);
			sleep(100);
		}

	return 0;
}
