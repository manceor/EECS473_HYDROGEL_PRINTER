#include <stdio.h>

char line[64];

int main(void) {
	FILE* fp1;
	FILE* fp2;
	
	fp1 = fopen("CE3_3DBenchy.gcode", r);
	fp2 = fopen("parsed_benchy.txt", w);
	
	fscanf(fp1, "%[^\n]", line);
	
	return 0;
}
