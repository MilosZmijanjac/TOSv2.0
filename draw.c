#include "testvga.h"
#include "math.h"
#include "vga.h"
#include "kb.h"
#include "monitor.h"
unsigned char VGA[240*320]; 
long SIN_ACOS[1024];

void circle_fast(int x,int y, int radius, unsigned char color)
{
  long n=0,invradius=(1/(float)radius)*0x10000L;
  int dx=0,dy=radius-1;
  unsigned short  dxoffset,dyoffset,offset = (y<<8)+(y<<6)+x;

  while (dx<=dy)
  {
    dxoffset = (dx<<8) + (dx<<6);
    dyoffset = (dy<<8) + (dy<<6);
    VGA[offset+dy-dxoffset] = color;  /* octant 0 */
    VGA[offset+dx-dyoffset] = color;  /* octant 1 */
    VGA[offset-dx-dyoffset] = color;  /* octant 2 */
    VGA[offset-dy-dxoffset] = color;  /* octant 3 */
    VGA[offset-dy+dxoffset] = color;  /* octant 4 */
    VGA[offset-dx+dyoffset] = color;  /* octant 5 */
    VGA[offset+dx+dyoffset] = color;  /* octant 6 */
    VGA[offset+dy+dxoffset] = color;  /* octant 7 */
    dx++;
    n+=invradius;
    dy = (int)((radius * SIN_ACOS[(int)(n>>6)]) >> 16);
  }
}
unsigned char VGAM[240][320];
void draw_linear(int k, int n)//y=kx+n
{int y,z;
vga_init(G320x200x256);
vga_initpalette();
vga_clear_screen();
	for(y=0;y<200;y++)
	{
        for(z=0;z<320;z++)
		{        
            vga_pixel(z,y,82);                
        	}
	}
	for(y=0;y<240;y++)
	{
	  if(y%10==0)
	     VGAM[y][160]=50;
	  else
 	     VGAM[y][160]=100;
	}
	for(z=0;z<320;z++)
	{
	  if(z%10==0)
 	     VGAM[100][z]=50;
	  else
 	     VGAM[100][z]=100;
	}


	for(double x=-160.0;x<=160.0;x+=0.001)
	{
          y=myround(k*x+n);
  
        	if(((y+100)<=240)&&((100-y)>=0))
        	{
		  VGAM[100-(int)y][160+(int)x]=100;
		}
	}
	for(y=0;y<200;y++)
	{
        	for(z=0;z<320;z++)
		{        
                 vga_pixel(z,y,VGAM[y][z]);                
                }
	}
vga_blit();
getchar();
vga_clear_screen();
vga_init(TEXT_MODE);
vga_text_clear();
vga_blit();
cls();
}

void draw_quad(int a, int b, int c)//y=ax^2+bx+c
{int y,z;
vga_init(G320x200x256);
vga_initpalette();
vga_clear_screen();
	for(y=0;y<200;y++)
	{
        for(z=0;z<320;z++)
		{        
            vga_pixel(z,y,82);                
        	}
	}
	for(y=0;y<240;y++)
	{
	  if(y%10==0)
	     VGAM[y][160]=50;
	  else
 	     VGAM[y][160]=100;
	}
	for(z=0;z<320;z++)
	{
	  if(z%10==0)
 	     VGAM[100][z]=50;
	  else
 	     VGAM[100][z]=100;
	}


	for(double x=-160.0;x<=160.0;x+=0.001)
	{
          y=myround(a*x*x+b*x+c);
  
        	if(((y+100)<=240)&&((100-y)>=0))
        	{
		  VGAM[100-(int)y][160+(int)x]=100;
		}
	}
	for(y=0;y<200;y++)
	{
        	for(z=0;z<320;z++)
		{        
                 vga_pixel(z,y,VGAM[y][z]);                
                }
	}
vga_blit();
getchar();
vga_clear_screen();
vga_init(TEXT_MODE);
vga_text_clear();
vga_blit();
cls();
}

void draw_circle(int p,int q, int r){//(x-p)^2+(y-q)^2=r^2
vga_init(G320x200x256);
vga_initpalette();
vga_clear_screen();
int x,y;
for(y=0;y<200;y++){
        for(x=0;x<320;x++){        
            vga_pixel(x,y,82);                
        }
    }
 for(int i=0;i<1024;i++)                 /* create the sin(arccos(x)) table. */
  {
    SIN_ACOS[i]=sin(acos((float)i/1024))*0x10000L;
  }
 circle_fast(p,q,r,100);
  
    for(y=0;y<200;y++){
        for(x=0;x<320;x++){        
            vga_pixel(x,y,VGA[320*y+x]);                
        }
    }
vga_blit();
getchar();
vga_clear_screen();
vga_init(TEXT_MODE);
vga_text_clear();
vga_blit();
cls();
return;
}
