#include <stdio.h>
#include <string.h>

#define MAXLENGTH 64

#pragma warning(disable: 4996)

int main(void) {
	FILE* fp1;
	FILE* fp2;

	char line[MAXLENGTH];

	fp1 = fopen("CE3_3DBenchy.gcode", "r");
	fp2 = fopen("parsed_benchy.txt", "w");

	while (fgets(line, MAXLENGTH, fp1) != NULL) {
		if (line[0] != ';') {
			sscanf(line, "%[^;]s", line);
			fprintf(fp2, line);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
