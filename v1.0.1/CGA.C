/*
VGA GRAPHICS FRAMEWORK FOR DOS (C88 16 bit).
DEMO IN main()
IMAGE FORMAT: .TPA (Text Pixel Array) UNCOMPRESSED FORMAT
SAMPLE FILES INCLUDED.
HAVE FUN!
*/

#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <conio.h>

#include "PSOUNDDX.h"

void setmode(unsigned char mode) { /* sets video mode*/
	union REGS regs;
	regs.h.ah = 0x00;
	regs.h.al = mode;
	int86(0x10, &regs, &regs);
}

int imgbuff[8][8] = {
	{65,65,1,1,1,1,65,65},
	{65,1,17,17,17,17,1,65},
	{1,17,15,15,17,17,17,1},
	{1,17,15,17,17,17,9,1},
	{1,17,17,17,17,9,9,1},
	{1,17,17,17,9,9,18,1},
	{65,1,9,9,9,18,1,65},
	{65,65,1,1,1,1,65,65}
};
int size = sizeof(imgbuff) / sizeof(imgbuff[0]);

int imgbuff1[8][8] = {
	{65,65,1,1,1,1,65,65},
	{65,1,17,17,17,17,1,65},
	{1,17,16,16,17,17,17,1},
	{1,17,16,17,17,17,9,1},
	{1,17,17,17,17,9,9,1},
	{1,17,17,17,9,9,18,1},
	{65,1,9,9,9,18,1,65},
	{65,65,1,1,1,1,65,65}
};

int imgbuff2[8][8] = {
	{65,65,1,1,1,1,65,65},
	{65,1,17,17,17,17,1,65},
	{1,17,16,16,17,17,17,1},
	{1,17,16,17,17,17,9,1},
	{1,17,17,17,17,9,9,1},
	{1,17,17,17,9,9,18,1},
	{65,1,9,9,9,18,1,65},
	{65,65,1,1,1,1,65,65}
};

int beep_Hz;
int beep_C;

/* 1.059463 */

int snd_a4 = 440;
int snd_ash4 = 466;
int snd_b4 = 494;
int snd_c4 = 523;
int snd_csh4 = 554;
int snd_d4 = 587;
int snd_dsh4 = 622;
int snd_e4 = 659;
int snd_f4 = 698;
int snd_fsh4 = 739;
int snd_g4 = 783;
int snd_gsh4 = 830;

char imagealias[] = "";
char dbug[] = "";
char in1;
int filecon;
int i;
int x;
int y;
int z;
int tpaw, tpah;
int charcon;
int glx;
int gly;
int glz;
int guiy;
int glx1;
int gly1;
int arrx;
int arry;
int spritecon;
int sprx;
int spry;
int sprz;
int vga_r;
int vga_g;
int vga_b;
int vga_value;
char loadbuff_pixelarray[] = "";
void plot(x, y, z) { /* puts a pixel on the screen [plot(x,y,color)] */
	unsigned char far* CGA = (unsigned char far*)0xA0000000;
	CGA[y * 320 + x] = z;
}

void svga(vga_value, vga_r, vga_g, vga_b) {
	  outp(0x3C8, vga_value);
	  outp(0x3C9, vga_r);
	  outp(0x3C9, vga_g);
	  outp(0x3C9, vga_b);
}

void lineadd(glx, gly, glx1, gly1, z) {
	while (glx != glx1) {
		plot(glx, gly, z);
		glx++;
	}
	while (gly != gly1) {
		plot(glx, gly, z);
		gly++;
	}
}

void fillscr(glx1, gly1, glx, gly, z) {
	while (glx != glx1) {
		plot(glx, gly, z);
		glx--;
	}
	while (gly != gly1) {
		plot(glx, gly, z);
		gly--;
	}
}

void rect(glx, gly, glx1, gly1, z)  {
	glz = glx;
	while (gly != gly1) {
		plot(glx, gly, z);
		glx++;
		if(glx == glx1) {
			gly++;
			glx = glz;
		}
	}
}

void gui1(glx, gly, glx1, gly1, z)  {
	glz = glx;
	guiy = gly;
	while (gly != gly1) {
		plot(glx, gly, z);
		glx++;
		if(glx == glx1) {
			gly++;
			glx = glz;
		}
	}
	lineadd(glz, guiy, glz, gly1, 15);
	lineadd(glz, gly1, (glx1 + 1), gly1, 8);
	lineadd(glx1, guiy, glx1, gly1, 8);
	lineadd(glz, guiy, (glx1 + 1), guiy, 15);
}

void drawbuff(glx, gly) {
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		glx1 = glx + arrx;
		gly1 = gly + arry;
		if(imgbuff[arry][arrx] != 65) plot(glx1, gly1, imgbuff[arry][arrx]);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
}

void drawbuff1(glx, gly) {
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		glx1 = glx + arrx;
		gly1 = gly + arry;
		if(imgbuff1[arry][arrx] != 65) plot(glx1, gly1, imgbuff1[arry][arrx]);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
}

void drawbuff2(glx, gly) {
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		glx1 = glx + arrx;
		gly1 = gly + arry;
		if(imgbuff2[arry][arrx] != 65) plot(glx1, gly1, imgbuff2[arry][arrx]);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
}

void loadbuff(char* imagealias) {
	FILE* file = fopen(imagealias, "r");
	if(!file) {
		setmode(0x03);
		cprintf("%s NOT FOUND!", imagealias);
		return;
	}
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		fscanf(file, "%s", loadbuff_pixelarray);
		imgbuff[arry][arrx] = atoi(loadbuff_pixelarray);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
	fclose(file);
}

void loadbuff1(char* imagealias) {
	FILE* file = fopen(imagealias, "r");
	if(!file) {
		setmode(0x03);
		cprintf("%s NOT FOUND!", imagealias);
		return;
	}
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		fscanf(file, "%s", loadbuff_pixelarray);
		imgbuff1[arry][arrx] = atoi(loadbuff_pixelarray);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
	fclose(file);
}

void loadbuff2(char* imagealias) {
	FILE* file = fopen(imagealias, "r");
	if(!file) {
		setmode(0x03);
		cprintf("%s NOT FOUND!", imagealias);
	}
	arrx = 0;
	arry = 0;
	while (arry != 8) {
		fscanf(file, "%s", loadbuff_pixelarray);
		imgbuff2[arry][arrx] = atoi(loadbuff_pixelarray);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
	fclose(file);
}

void snd_beep(int beep_Hz, int beep_C) {
	sound(beep_Hz);
	delay(beep_C);
	nosound();
}

void drawfile(const char* imagealias, int glx, int gly, int tpaw, int tpah) {
	FILE* file = fopen(imagealias, "r");
	arrx = 0;
	arry = 0;
	while (arry != tpah) {
		glx1 = glx + arrx;
		gly1 = gly + arry;
		fscanf(file, "%s", loadbuff_pixelarray);
		filecon = atoi(loadbuff_pixelarray);
		if(filecon != 65) plot(glx1, gly1, filecon);
		arrx++;
		if (arrx == tpaw) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
	fclose(file);
}

void letter(int glx, int gly, int charcon) {
	FILE* file = fopen("charset.tpa", "r");
	arrx = 0;
	arry = 0;
	charcon = charcon * 64;
	while (charcon != 0) {
		fscanf(file, "%s", loadbuff_pixelarray);
		charcon--;
	}
	while (arry != 8) {
		glx1 = glx + arrx;
		gly1 = gly + arry;
		fscanf(file, "%s", loadbuff_pixelarray);
		filecon = atoi(loadbuff_pixelarray);
		if(filecon != 65) plot(glx1, gly1, filecon);
		arrx++;
		if (arrx == 8) {
			arry++;
			glx1 = 0;
			arrx = 0;
		}
	}
	fclose(file);
}
int main() {
	printf("\nCAR.");
	getch();
	setmode(0x13);
	svga(16, 15,15,15);
	svga(17, 33, 33, 63);
	svga(18, 0,0,53);
	rect(0,0,320,200,7);
	while (1) {
		drawbuff(sprx, spry);
		guitar(sprx, 15);
		rect(sprx,spry,(sprx + 8),(spry + 8),7);
		sprx = sprx + 4;
		spry++;
		if(spry == 384) {
			break;
		}
	}
	rect(0,0,320,200,16);
	delay(1000);
	sprx = 107;
	loadbuff("car.tpa");
	for(i = 0; i != 2; i++) {
		guitar(snd_e4 / 2,107);
		guitar(snd_g4 / 2,107);
		guitar(snd_b4, 107);
		guitar(snd_e4,107);
	}
	gui1(143,83,176,116,7);
	svga(16, 25,25,25);
	loadbuff1("GRAS1.tpa");
	drawfile("ROAD.TPA", 152,84,16,16);
	drawfile("ROAD.TPA", 152,100,16,16);
	drawbuff(160,sprx);
	drawbuff1(168,84);
	drawbuff1(168, 92);
	drawbuff1(168, 100);
	drawbuff1(168, 108);
	drawbuff1(144,84);
	drawbuff1(144,92);
	drawbuff1(144,100);
	drawbuff1(144,108);
	sprx = sprx - 2;
	for(i = 0; i != 4; i++) {
		guitar(snd_b4 / 2,107);
		drawbuff(160,sprx);
		guitar(snd_d4 / 2,107);
		sprx = sprx - 2;
		guitar(snd_e4 / 2, 107);
		svga(16, 25,25,25);
		guitar(snd_a4,107);
		svga(16,50,50,50);
		guitar(snd_b4 / 2,107);
		drawbuff(160,sprx);
		guitar(snd_d4 / 2,107);
		guitar(snd_a4, 107);
		sprx = sprx - 2;
		guitar(snd_e4 / 2,107);
		svga(16,10,10,10);
		guitar(snd_e4 / 2,107);
		svga(16, 25,25,25);
		guitar(snd_g4 / 2,107);
		svga(16,50,50,50);
		guitar(snd_b4, 107);
		svga(16, 25,25,25);
		guitar(snd_e4,107);
		svga(16, 10,10,10);
		guitar(snd_e4 / 2,107);
		svga(16, 25,25,25);
		guitar(snd_g4 / 2,107);
		svga(16, 50,50,50);
		guitar(snd_b4, 107);
		svga(16, 25,25,25);
		guitar(snd_e4,107);
		svga(16, 10,10,10);
	}
	setmode(0x03);
	return 0;
}