////////////////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************************
This program is filter to leave sixth clumn, basic type of word.
This program's argument is part of mecab matrix except first clumn and numbers of words.
***********************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

const int max_size = 2000;

int main(int argc,char *argv[]){
	FILE *input, *output;
	long long words;
	char inp_name[50], out_name[50];
	char *strw;
	int chr, cun = 0;
	long long i = 0,j = 0;
	//Cheak argument and open files
	if(argc != 4){
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
	
	words = atoi(argv[3]);
	printf("%d\n",words);

	//Make array for words.
	strw = (char *)malloc((long long)words * 50 * sizeof(char));

	while((chr = fgetc(input)) != EOF){
		if(chr == ',') cun++;
		if(cun == 4){
			strw[j * 50 + i] = chr;
			i++;
		}
		if(chr == '\n'){
			 cun = 0;
			 i = 0;
			 j++;
		}
		
	}

	for(j =0;j < words; j++){
		i =0;
		while(strw[j * 50 +i] != '\n'){
			printf("%c",strw[j * 50 + i]);
			i++;
		}
		printf("\n");
	}
}
