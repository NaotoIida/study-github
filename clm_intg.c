/////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************************************************
  This is the program for converting words into archetypes.
  This program needs argures about mecab's first clumn, sixth clumn, output file mame, and munbers of lines.
  **********************************************************************************************/
/////////////////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

const long long max_w =50;			 	       //max word length

int main(int argc,char *argv[]){
	FILE *firin, *sixin, *output;
	char fir_name[max_w], six_name[max_w], out_name[max_w];//variable of file name
	long long i;
	long long lines;				       //number of words in sentence
	char *firvoc, *sixvoc, *outvoc;			       //each file's array's pointer

    //Cheak argument and opne files
	if(argc != 5){
		puts("Misstake about argument.");
		return -1;
	}

	strcpy(fir_name,argv[1]);
	firin = fopen(fir_name,"r");
	if(firin == NULL){
		puts("First clumn file not found.");
		return -1;
	}

	strcpy(six_name,argv[2]);
	sixin = fopen(six_name,"r");
	if(sixin == NULL){
		puts("Sixth clumn file not found.");
		return -1;
	}

	strcpy(out_name,argv[3]);
	output = fopen(out_name,"w");
	if(output == NULL){
		puts("Output file not found.");
		return -1;
	}
	
	lines = atoi(argv[4]);

    //Create arrays for vocabrariy
	firvoc = (char *)malloc((long long)lines*max_w*sizeof(char));
	sixvoc = (char *)malloc((long long)lines*max_w*sizeof(char));
	outvoc = (char *)malloc((long long)lines*max_w*sizeof(char));

    //input words into vocabraly arrays
	i = 0;
	while(fgets(&firvoc[i*max_w*sizeof(char)], max_w, firin) != NULL){
		i++;
	}

	i = 0;
	while(fgets(&sixvoc[i*max_w*sizeof(char)], max_w, sixin) != NULL){
		i++;
	}	

    //Comper and convert words
	for(i=0;i<lines;i++){
		if(strcmp(&firvoc[i*max_w*sizeof(char)],&sixvoc[i*max_w*sizeof(char)]) == 0){
				strcpy(&outvoc[i*max_w*sizeof(char)],&sixvoc[i*max_w*sizeof(char)]);
			}else{
			if(sixvoc[i*max_w*sizeof(char)] != '*'){
				strcpy(&outvoc[i*max_w*sizeof(char)],&sixvoc[i*max_w*sizeof(char)]);
				}else{
				strcpy(&outvoc[i*max_w*sizeof(char)],&firvoc[i*max_w*sizeof(char)]);
				}
			}
		}

    //Putout outvoc to output file of argument.
	for(i=0;i<lines;i++){
		fputs(&outvoc[i*max_w*sizeof(char)],output);
	}

    // Close files and release malloc functions
	fclose(firin);
	fclose(sixin);
	fclose(output);
	free(firvoc);
	free(sixvoc);
	free(outvoc);
}
