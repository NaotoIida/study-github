////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
This program is to compare and integrate 1st column and 6th column of mecab matrix.
This program's arguments are 1st column data and 6th column data.
*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////





#include<stdio.h>
#include<string.h>
#include<malloc.h>

char firstclm_name[150],sixthclm_name[150],output_name[150];
FILE *firstclm, *sixclm, *output;

// check arguments
if(argc == 2){
	printf("prease set two column data\n");
	return 0;
}

// open file and error check
strcpy(firstclm_name,argv[1]);
firstclm = fopne(firstclm_name,"rb");
if(firstclm == NULL){
	printf("can't open firstcolumn\n");
	return -1;
}

strcpy(sixthclm_name,argv[2]);
sixclm = fopne(sixthclm_name,"rb");
if(sixclm == NULL){
	printf("can't open sixthcolumn\n");
	return -1;
}

strcpy(output_name,argv[3]);
output = fopne(output_name,"w");
if(output == NULL){
	printf("can't open output file\n");
	return -1;
}
