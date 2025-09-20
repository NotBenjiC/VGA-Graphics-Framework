#include <stdio.h>
#include <conio.h>
#include <dos.h>

int running = 1;

char userchar;
char subpix = -37;

int x;
int y;
int arrx;
int arry;
int eposx;
int eposy;
int selcol = 0;

int canvas[16][16] = {
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3}
};

void setcursor(x, y) {
	union REGS r;
	r.h.ah = 2;
	r.h.bh = 0;
	r.h.dh = y;
	r.h.dl = x;
	int86(0x10, &r, &r);
}

void drawcanvas() {
	arrx = 0;
	arry = 0;
	y = 1;
	setcursor(1,1);
	while (arry != 16) {
		if(canvas[arry][arrx] == 0) {
			textcolor(0);
		} else if(canvas[arry][arrx] == 1) {
			textcolor(1);
		} else if(canvas[arry][arrx] == 2) {
			textcolor(2);
		} else if(canvas[arry][arrx] == 3) {
			textcolor(3);
		} else if(canvas[arry][arrx] == 4) {
			textcolor(4);
		} else if(canvas[arry][arrx] == 5) {
			textcolor(5);
		} else if(canvas[arry][arrx] == 6) {
			textcolor(6);
		} else if(canvas[arry][arrx] == 7) {
			textcolor(7);
		} else if(canvas[arry][arrx] == 8) {
			textcolor(8);
		} else if(canvas[arry][arrx] == 9) {
			textcolor(9);
		} else if(canvas[arry][arrx] == 10) {
			textcolor(10);
		} else if(canvas[arry][arrx] == 11) {
			textcolor(11);
		} else if(canvas[arry][arrx] == 12) {
			textcolor(12);
		} else if(canvas[arry][arrx] == 13) {
			textcolor(13);
		} else if(canvas[arry][arrx] == 14) {
			textcolor(14);
		} else if(canvas[arry][arrx] == 15) {
			textcolor(15);
		}
		cprintf("%c%c", subpix, subpix);
		arrx++;
		if(arrx == 16) {
			arrx = 0;
			arry++;
			y++;
			setcursor(1,y);
		}
	}
}

void savetotpa() {
	FILE* file = fopen("SAVDIMG.TPA", "w");
	arrx = 0;
	arry = 0;
	while (arry != 16) {
		fprintf(file, "%d ", canvas[arry][arrx]);
		arrx++;
		if(arrx == 16) {
			arrx = 0;
			arry++;
		}
	}
	fclose(file);
}

void load() {
	FILE* file = fopen("loadimg.tpa", "r");
	arrx = 0;
	arry = 0;
	while (arry != 16) {
		fscanf(file, "%d ", canvas[arry][arrx]);
		arrx++;
		if(arrx == 16) {
			arrx = 0;
			arry++;
		}
	}
	fclose(file);
}

void user() {
	userchar = getch();
	if(userchar == 'w') {
		if(eposy != 0) eposy--;
	} else if(userchar == 'a') {
		if(eposx != 0) eposx--;
	} else if(userchar == 's') {
		if(eposy != 15) eposy++;
	} else if(userchar == 'd') {
		if(eposx != 15) eposx++;
	} else if(userchar == 'x') {
		if(canvas[eposy][eposx] != 0) canvas[eposy][eposx]--;
	} else if(userchar == 'c') {
		if(canvas[eposy][eposx] != 15) canvas[eposy][eposx]++;
	} else if(userchar == 'v') {
		canvas[eposy][eposx] = canvas[eposy][eposx] + 8;
	} else if(userchar == 'z' || userchar == 'y') {
		canvas[eposy][eposx] = canvas[eposy][eposx] - 8;
	} else if(userchar == '1') {
		if(selcol != 0) selcol--;
	} else if(userchar == '2') {
		if(selcol != 15) selcol++;
	} else if(userchar == 'b') {
		canvas[eposy][eposx] = selcol;
	} else if(userchar == 'l') {
		load();
	} else if(userchar == 'r') {
		savetotpa();
	} else if(userchar == 'm') running--;
}


int main() {
	setcursor(30, 0);
	printf("TPA EDITOR");
	getch();
	while (running) {
		clrscr();
		printf(" 0 1 2 3 4 5 6 7 8 9 A B C D E F\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nA\nB\nC\nD\nE\nF");
		drawcanvas();
		textbackground(0);
		textcolor(15);
		printf("\neditor pos: %d, %d, sel color: %d\n", eposx, eposy, selcol);
		printf("WASD to move, XC, ZV to manipulate color, R to save, M to exit.\n1, 2 to edit selected color, B to use sel color, L to load (loadimg.tpa).");
		user();

	}
	getch();
}