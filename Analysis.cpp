#include <string.h>

#include "Analysis.h"

Analysis::Analysis()
{
	this->type = -1;
	this->param = NULL;
}

Analysis::Analysis(Analysis &a)
{
	char *str = a.getParam();
	int length = strlen(str);

	this->type = a.getType();
	this->param = new char[length];

	strcpy(this->param, str);
}

Analysis::~Analysis()
{
	if(this->param)
		delete this->param;
}

void Analysis::setParam(const char *param) 
{
	int length = strlen(param);

	if(this->param)
		delete this->param;

	this->param = new char[length];

	strcpy(this->param, param);
}
