#include <stdio.h>
#include <syscall.h>
#include <cstring>
#include <memory>
#include <dayos.h>

char* framebuffer;

void setup_vga()
{
	int y;

	// wait for key
	//syscall2(16, 0x16, 0x0);

	// switch to 320x200x256 graphics mode
	syscall2(16, 0x10, 0x13); //0x18f);

	framebuffer = (char*) 0xA0000;
	// full screen with blue color (1)
	memset ((char*) 0xA0000, 1, (320 * 200));

	// draw horizontal line from 100,80 to 100,240 in multiple colors
	//for (y = 0; y < 200; y++)
	//	memset ((char*) 0xA0000 + (y * 320 + 80), y, 160);

	// wait for key
	//	syscall2(16, 0x16, 0x0);

	// switch to 80x25x16 text mode
	//syscall2(16, 0x10, 0x0003);
}

void put_pixel(int x, int y, int color)
{
	framebuffer[y*320+x] = color;
}

void slow_fill(int x, int y, int w, int h, int color)
{
	for(int i = x; i < x + w; i++)
		for(int j = y; j < y + h; j++)
			put_pixel(i, j, color);
}

void fast_fill(int x, int y, int w, int h, int color)
{
	char* where = framebuffer + (y*320+x);
	for(int i = 0; i < w; i++)
		{
			for(int j = 0; j < h; j++)
			{
				where[j] = color;
				//put_pixel(i, j, color);
			}

			where += 320;
		}
}

int main(int argc, char* argv[])
{
	setup_vga();

	int x = 0, y = 0;
	int w = 30, h = 30;
	int dirx = 3, diry = 2;

	while(1)
		{
			// Clear rect
			fast_fill(x, y, w, h, 1);
			
			x += dirx;
			y += diry;

			if(x <= 0 || x + w >= 320)
				dirx = -dirx;

			if(y <= 0 || y + h >= 200)
				diry = -diry;


			// draw rect
			fast_fill(x, y, w, h, 4);

			sleep(20);
		}
	while(1);
	return 0;
}
