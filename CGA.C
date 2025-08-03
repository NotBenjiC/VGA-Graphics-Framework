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

void setmode(unsigned char mode) { /* sets video mode*/
	union REGS regs;
	regs.h.ah = 0x00;
	regs.h.al = mode;
	int86(0x10, &regs, &regs);
}

int imgbuff[8][8] = {
	{65,65,1,1,1,1,65,65},
	{65,1,17,17,17,17,1,65},
	{1,17,16,16,17,17,17,1},
	{1,17,16,17,17,17,9,1},
	{1,17,17,17,17,9,9,1},
	{1,17,17,17,9,9,18,1},
	{65,1,9,9,9,18,1,65},
	{65,65,1,1,1,1,65,65}
};

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
int x;
int y;
int z;
int tpaw, tpah;
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
		return;
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


int main() {
	setmode(0x13);
	/*
	svga(1, 170, 170, 170);
	svga(2, 0, 0, 170);
	svga(3, 0, 170, 84);
	svga(4, 170, 0, 84);
	*/
	svga(16, 32, 16, 0);
	plot(13, 17, 16);
	svga(17, 0, 0, 25);
	svga(18, 0, 0, 212);
	drawbuff(5, 5);
	delay(1200);
	loadbuff("img1.tpa");
	rect(0,0,319,199,7);
	lineadd(0, 0, 320, 200, 15);
	lineadd(1, 199, 320, 199, 8);
	lineadd(319, 1, 319, 199, 8);
	rect(5, 5, 15, 15, 6);
	while (!spritecon) {
		drawbuff(sprx, spry);
		sprx++;
		spry++;
		if(sprx == 200) spritecon = 1;
	}
	delay(120);
	gui1(0,0,319,199,7);
	gui1(8, 8, 17, 17, 7);
	drawbuff(9, 9);
	gui1(24,24,48,48,7);
	rect(50,50,80,70,9);
	gui1(160, 100, 168, 108, 4); /* 88x49 */
	loadbuff1("b1.tpa");
	loadbuff2("bush.tpa");
	drawbuff1(161,100);
	gui1(0,0,319,199, 7);
	gui1(114,75,203,125, 17);
	gui1(114, 67, 203, 75, 1);
	gui1(114, 67, 122, 75, 7);
	lineadd(116,71,121,71,8);
	plot(114,75, 15);
	drawbuff1(115,117);
	drawbuff1(123,117);
	drawbuff1(131,117);
	drawbuff1(139,117);
	drawbuff1(147,117);
	drawbuff1(155,117);
	drawbuff1(163,117);
	drawbuff1(171,117);
	drawbuff1(179,117);
	drawbuff1(187,117);
	drawbuff1(195,117);
	drawbuff2(187,109);
	drawfile("cstl1.tpa", 187, 101, 16, 16);
	sprx = 123;
	plot(123, 85, 14);
	plot(144,96,14);
	plot(155, 84, 14);
	plot(166, 105, 14);
	plot(185, 95, 14);
	while (spritecon) {
		drawbuff(sprx,109);
		/*drawbuff2(187,109); */
		drawbuff2(195, 109);
		in1 = getch();
		if(in1 == 'd') {
			spry = sprx;
			sprx++;
		} else if(in1 == 'a') {
			spry = sprx;
			sprx--;
		} else if(in1 == 'q') spritecon--;
		if(sprx == 114) {
			sprx++;
			spry++;
		} else if(sprx == 196) {
			sprx--;
			spry--;
		}
		sprz = spry + 8;
		rect(spry,109,sprz,117, 17);

	}
	snd_beep(snd_a4, 100);
	snd_beep(snd_ash4, 100);
	snd_beep(snd_b4, 100);
	snd_beep(snd_c4, 100);
	snd_beep(snd_csh4, 100);
	snd_beep(snd_d4, 100);
	snd_beep(snd_dsh4, 100);
	snd_beep(snd_e4, 100);
	snd_beep(snd_f4, 100);
	snd_beep(snd_fsh4, 100);
	snd_beep(snd_g4, 100);
	snd_beep(snd_gsh4, 100);

	snd_beep(snd_d4, 600);
	snd_beep(snd_dsh4, 600);
	snd_beep(snd_g4, 600);
	snd_beep(snd_f4, 600);
	snd_beep(snd_g4, 600);
	snd_beep(snd_ash4 * 2, 600);
	snd_beep(snd_f4, 600);
	snd_beep(snd_dsh4, 600);
	snd_beep(snd_c4, 600);
	snd_beep(snd_d4, 600);
	snd_beep(snd_c4, 600);
	snd_beep(snd_ash4, 600);
	snd_beep(snd_dsh4, 600);
	snd_beep(snd_d4, 600);
	snd_beep(snd_c4, 600);
	snd_beep(snd_ash4, 600);

	drawfile("x.tpa", 5, 5, 8, 8);

	setmode(0x03);
	return 0;
}