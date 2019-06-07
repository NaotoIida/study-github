////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************
This program is to change ',' to '\t' in matrix.
This program's argument are part of mecab matrix except first clumn and out put file name.
***********************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	FILE *input, *output;
	char inp_name[50], out_name[50];
	int chr = 0;

	//Cheak argument and open files
	if(argc != 3){
		printf("Misstake of argument.\n");
		return -1;
	}

	strcpy(inp_name,argv[1]);
	input = fopen(inp_name,"r");
	if(input == NULL){
		printf("Input file not found.\n");
		return -1;
	}

	strcpy(out_name,argv[2]);
	output = fopen(out_name,"w");
	if(output == NULL){
		printf("Output file not found.\n");
		return -1;
	}
	

	//change ',' to '\t'.
	while((chr = fgetc(input)) != EOF){
		if(chr == ',') fprintf(output,"\t");
		else fprintf(output,"%c",chr);
	}

	fclose(input);
	fclose(output);
}
