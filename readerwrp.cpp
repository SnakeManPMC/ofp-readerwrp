#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *map;
	FILE *text;
	char sig[33];
	short Elevation=0,LowElev=0,HighElev=0,TexIndex=0;
	int MapSize=256;


	map=fopen("pmcworld.wrp","rb");
	if (!map) {printf("error in pmcworld.wrp\n");exit(1);}

	text=fopen("wrpread.txt","wt");
	if (!text) {printf("error at wrpdebug.txt\n");exit(1);}


		/* - signature - 4 bytes */
	fread(sig,4,1,map);
	sig[4]=0;
	fprintf(text, "sig: %s\n",sig);

	/* X size  */
	fread(&MapSize,4,1,map);
	fprintf(text, "x size: %d\n",MapSize);

	/* Y size */
	fread(&MapSize,4,1,map);
	fprintf(text, "x size: %d\n",MapSize);

	printf("Reading WRP file, size: %d...\n",MapSize);

	/* read elevations */
	fread(&Elevation,2,1,map);
	for (int ic=0; ic < MapSize*MapSize; ic++) {
	fprintf(text, "elevation [%d]: %d\n",ic,Elevation);
		
		if (LowElev > Elevation) LowElev=Elevation;
		if (HighElev < Elevation) HighElev=Elevation;

		fread(&Elevation,2,1,map);
	}

	/* read texture indexes */
	fread(&TexIndex,2,1,map);
	for (int cc=0; cc < MapSize*MapSize; cc++) {
	fprintf(text, "texture index [%d]: %d\n",cc,TexIndex);
		
		fread(&TexIndex,2,1,map);
	}


	/* textures 32 char length and total of 512 */
	for (int ix=0; ix < 512; ix++) {
		sig[0]=0;
	fread(sig,32,1,map);
	fprintf(text, "texture name [%d]: %s\n",ix,sig);
	}

fprintf(text,"\n****\nlowest elevation; %d, highest elevation: %d\n****\n",LowElev,HighElev);
printf("lowest elevation; %d, highest elevation: %d\n",LowElev,HighElev);
system("pause");

	fclose(map);
	fclose(text);
	return 0;
}
