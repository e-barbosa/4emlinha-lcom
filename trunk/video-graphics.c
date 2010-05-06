#include "video-graphics.h"
 
 
 void swap(int *a, int *b) 
{

   int t = *a;
   
   *a = *b;
   *b = t;
}

 char * enter_graphics(int mode, __dpmi_meminfo *map)
{


	__dpmi_regs regs;
	char *video_mem; // apontador genérico para aceder à memória gráfica 
	
	if (mode==0x4101)
		{
			HRES = 640;
			VRES = 480;
		}
	else if (mode==0x4103)
		{
			HRES = 800;
			VRES = 600;
		}
	else if (mode==0x4105)
		{
			HRES = 1024;
			VRES = 768;
		}
	else if (mode==0x4107)
		{
			HRES = 1280;
			VRES = 1024;
		}
	
	map->address = getAddress(*map);

	map->size = HRES*VRES;
	
	regs.x.ax = 0x4F02; // registo AX do CPU com valor 0x4f02 
	regs.x.bx = mode; // registo BX do CPU com valor 0x4105 
	__dpmi_int(0x10, &regs); // gera interrupção de software 0x10, activando o modo gráfico 
	
	__djgpp_nearptr_enable(); // permite acesso à memória física usando apontadores 
	__dpmi_physical_address_mapping(map); //video_mem contém o endereço genérico a usar 
	video_mem = (char *)(map->address + __djgpp_conventional_base);
	
	
	

	return video_mem;
}


/** Unmap video memory, disable near pointer and returns to text mode
 */
void leave_graphics(__dpmi_meminfo map)
{
	regs.x.ax = 0x0003; /* registo AX do CPU com valor 0x03 */
	__dpmi_int(0x10, &regs); /* gera interrupção software 0x10, entrando no modo texto */

}

/** Draws a pixel of color "color" at screen coordinates x, y at memory address "base"
 */
void set_pixel(int x, int y, int color, char *base)
{
	
	x = abs(x);
	y = abs(y);
	color = abs(color);
	*(base+HRES*y+x) = color;
	

}

/** Returns the pixel color at screen coordinates x, y at memory address "base"
 */
int get_pixel(int x, int y, char *base)
{
	x = abs(x);
	y = abs(y);
	
	return *(base+HRES*y+x);
}

/** Set graphics memory at memory address "base" to "color".
 */
void clear_screen(char color, char *base)
{
	int i,j;
	
	for(i = 0; i < HRES; i++)
		for(j = 0; j < VRES; j++)
		{
			set_pixel(i,j,color,base);
		}
}

/** Draw a line of color "color" between point (xi,yi) and (xf,yf) at memory address "base"
*/
void draw_line(int x0, int y0, int x1, int y1, int color, char *base)
{
	int steep = abs(y1 - y0) > abs(x1 - x0);
	int x,y;
	 
    if (steep)
	{	 
         swap(&x0, &y0);
         swap(&x1, &y1);
	}
	
    if (x0 > x1)
	{
         swap(&x0, &x1);
         swap(&y0, &y1);
	}
    
	int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
	 
    float error = 0.0;
    float deltaerr = ((float)deltay) / deltax;
    int ystep;
    y = y0;
	 
	 
    if (y0 < y1)
		ystep = 1;
	else
		ystep = -1;
		
	for(x = x0; x <= x1; x++)
	{
		if (steep) 
			set_pixel(y,x,color,base); 
		else 
			set_pixel(x,y,color,base);
			
		error += deltaerr;
		 
	    if (error >= 0.5)
		{
	             y += ystep;
	             error -= 1.0;
		}
	}
}

int getAddress(__dpmi_meminfo map)
{
	unsigned long dosbuf, address=0;
	
	map.address = address;

	dosbuf = __tb & 0xFFFFF; /* dosbuf é a área de transferência */
	dosmemput(&map.address, 4, dosbuf+40); /*apaga bytes 40 a 43 dessa área*/

	regs.x.ax = 0x4F01; /* VBE get mode info */
	regs.x.di = dosbuf & 0xF; /* LSB da área de transferência */
	regs.x.es = (dosbuf >> 4) & 0xFFFF; /*MSB da área de transferência*/
	regs.x.cx = 0x0105; /*informação sobre o modo 105h*/
	__dpmi_int(0x10, &regs); /* DOS int 10h */


	dosmemget(dosbuf+40, 4, &map.address); /* lê o endereço da memória vídeo */

	 
	return map.address;
}
