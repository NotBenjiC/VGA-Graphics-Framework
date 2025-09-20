/* SOUND.h
   INSTRUMENTS FOR PC SPEAKER
*/

#ifndef PSOUNDDX_H
#define PSOUNDDX_H

int SNDLIB_HZ;
int SNDLIB_TIME;

void guitar(SNDLIB_HZ, SNDLIB_TIME) {
	sound(SNDLIB_HZ * 2);
	delay(SNDLIB_TIME / 8);
	sound(SNDLIB_HZ);
	delay(SNDLIB_TIME);
	nosound();
}

#endif