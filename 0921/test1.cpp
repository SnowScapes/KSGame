#include <stdio.h>
#include <math.h>
#include <windows.h>
int calc_frequency(int octave, int inx);
int main(void) {
	int index[] = {7,7,9,9,7,7,4,7,7,4,4,2,7,7,9,9,7,7,4,7,4,2,4,0};
	int freq[24];
	for (int i=0; i<27; i++) 
		freq[i] = calc_frequency(4, index[i]);
	for (int i=0; i<=6; i++)
		Beep(freq[i],500);
	Sleep(1000);
	for (int i=7; i<=11; i++)
		Beep(freq[i],500);
	Sleep(1000);
	for (int i=12; i<=18; i++)
		Beep(freq[i],500);
	Sleep(1000);
	for (int i=19; i<=23; i++)
		Beep(freq[i],500);
	return 0;
}

int calc_frequency(int octave, int inx) {
	double do_scale=32.7032;
	double ratio=pow(2., 1/12.), temp;
	temp = do_scale*pow(2, octave-1);
	for (int i=0; i<inx; i++) {
		temp=(int)(temp+0.5);
		temp*=ratio;
	}
	return (int)temp;
}
