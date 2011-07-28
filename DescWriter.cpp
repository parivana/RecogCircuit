#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "desc_type.h"
#include "DescWriter.h"
#include "LinkedList.h"

static int ElementWriter(FILE *fp)
{
	Element *c = &listhead;
	// this function should return error code(<0) or 0;
	while(c->next != NULL) {
		c = c->next;
		switch(c->type) {
			case RESISTOR:
				fprintf(fp, "%s %d %d %.2lf\n", 
						c->name, c->pnode, c->nnode,
						c->param.value);
				break;
			case CAPACITOR:
				fprintf(fp, "%s %d %d %.2lf\n", 
						c->name, c->pnode, c->nnode,
						c->param.value);
				break;
			case INDUCTOR:
				fprintf(fp, "%s %d %d %.2lf\n", 
						c->name, c->pnode, c->nnode,
						c->param.value);
				break;
			case VSRC: // voltage source
				fprintf(fp, "%s %d %d %.2lf\n", 
						c->name, c->pnode, c->nnode,
						c->param.value);
				break;
			case ISRC: // current source
				fprintf(fp, "%s %d %d %.2lf\n", 
						c->name, c->pnode, c->nnode,
						c->param.value);
				break;

			default: // unknown element type
				return -1;
				break;
		}
	}


	return 0;
}

static int AnalysisWriter(FILE *fp, Analysis anl)
{
	// this function should return error code(<0) or 0;

	switch(anl.type) {
		case DC:
			fprintf(fp, ".DC %s %.2f %.2f %.2f\n",
					anl.u.dc.srcname, anl.u.dc.vstart, 
					anl.u.dc.vstop, anl.u.dc.vincr);
			break;
		case AC:
			fprintf(fp, ".AC ");
			if(anl.u.ac.type == 0) fprintf(fp, "DEC ");
			else if(anl.u.ac.type == 1) fprintf(fp, "OCT ");
			else if(anl.u.ac.type == 2) fprintf(fp, "LIN ");
			fprintf(fp, "%d %d %d\n", 
					anl.u.ac.np, anl.u.ac.fstart, anl.u.ac.fstop);
			break;
		case TRAN:
			fprintf(fp, ".TRAN %d %d\n", 
					anl.u.tran.tstep, anl.u.tran.tstop);
			break;
		default: // unknown analysis type
			return -1;
			break;
	}

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
