#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DescWriter.h"
#include "Element.h"
#include "Rect.h"
#include "Analysis.h"

static int ElementWriter(FILE *fp)
{
	return 0;
}

static int AnalysisWriter(FILE *fp, Analysis anl)
{
	// this function should return error code(<0) or 0;

	switch(anl.getType()) {
		default:
			break;
	}
	
	fprintf(fp, "%s\n", anl.getParam());
	return 0;
}

char *DescWriter(char *file, Analysis anl) 
{
	FILE *fp;
	char *fname;
	int ret;

	// file + ".cir";
	fname = (char *)malloc((strlen(file) + 4) * sizeof(char));
	strcpy(fname, file);
	strcat(fname, ".cir");
	fp = fopen(fname, "w+");
	if(fp == NULL) {
		fprintf(stderr, "Can't open %s\n", fname);
		exit(1);
	}

	fprintf(fp, "%s\n", fname);

	ret = ElementWriter(fp);
	if(ret < 0) {
		fprintf(stderr, "Element writing failed. error code: %d\n", ret);
		fclose(fp);
		exit(1);
	}

	ret = AnalysisWriter(fp, anl);
	if(ret < 0) {
		fprintf(stderr, "Analysis writing failed. error code: %d\n", ret);
		fclose(fp);
		exit(1);
	}

	fprintf(fp, ".END");
	fclose(fp);

	printf("Circuit description file %s created.\n", fname);
	return fname;
}
