#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#define j 10000

const long long max_size = 200;          // max length of strings
const long long max_w = 50;              // max length of vocabulary entries

int main(int argc, char *argv[]) {
  FILE *dicf,*inp,*outp;//バイナリファイルを読み込むストリーム
  char st1[max_size],stf[50];//I made stf[] for get a word from Wakatidate*.txt
  char file_name[max_size];//file_nameは引数のargvを格納する配列
  float len;
  long long words, size, a, b, c, d, cn, i;//wordsはバイナリファイルに登録してある単語の数,sizeは各分散ベクトルの次元数
  float *M;//*Mは概念行列を格納するポインタ
  char *vocab;
  long long lines;
  float ave_w[200] = {0}, tmp_w[200] = {0}, A[200] = {0};



  //confirmation of argument
  if (argc < 2) {
    printf("Usage: ./distance <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n");
    return 0;
  }


  //open file and error check
  strcpy(file_name, argv[1]);
  dicf = fopen(file_name, "rb");
  if (dicf == NULL) {
    printf("Binary file not found\n");
    return -1;
  }
  
  lines = atoi(argv[2]);

  strcpy(file_name, argv[3]);
  inp = fopen(file_name, "r");
  if (inp == NULL) {
    printf("Input file not found\n");
    return -1;
  }

  strcpy(file_name,argv[4]);
  outp = fopen(file_name, "w");
  if (outp== NULL) {
    printf("Output file not found\n");
    return -1;
  }


  words=4536628;
  size=200;
  

  //Reserve memory for Co-occurense matrix
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));     

  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;

  }


  //Make dictionary for searching. vocab[] is word dictionary and M[] is distributed representation dictionary.
  for (b = 0; b < words; b++) {
 	 a = 0;
	 //Put in words to vocab[] each ont charactors. 
   	 while (1) {
     		 vocab[b * max_w + a] = fgetc(dicf);
     		 if (feof(dicf) || (vocab[b * max_w + a] == ' ')) break;
     		 if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
    	}
   	vocab[b * max_w + a] = 0;
	//Put in number to M[].
   	for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, dicf);
    	//Normaliz M[]'s number.
    	len = 0;
    	for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    	len = sqrt(len);
   	for (a = 0; a < size; a++) M[a + b * size] /= len;
  }


  fclose(dicf);
  
  while (fgets(stf,50,inp)!=NULL) {
  	 //Put in input file's word to st1 array.
	 a = 0;
  	 while (1) {
     		 st1[a] = stf[a];
     		 if ((st1[a] == '\n') || (a >= max_size - 1)) {
       			 st1[a] = 0;                                                            //I donot know why put in 0 at the end.
      			  break;
     	         }
     		 a++;
   	 }
	 //Search the input word from vocabrary dictionary.
	 a = 0;
     		 for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], &st1[a])) break;
     		 if (b == words) b = -1;
     		 printf("\nWord: %s  Position in vocabulary: %lld\n", &st1[a], b);
      		//error that the target word does not appear in the dictionaly
     		 if (b == -1) {
       			 printf("Out of dictionary word!\n");
       			 continue;
     		 }
	 a=0;
  	 while(st1[a]!=0){
   		fprintf(outp,"%c",st1[a]);
		printf("%c",st1[a]);
		a++;
  	 }
	 puts("");
  	 fprintf(outp,",");
  	 for(a=0;a<size;a++){
   		fprintf(outp,"%f,",M[a+b*size]);
		printf("%f",M[a+b*size]);
		ave_w[a] += (100*M[a+b*size]);
  	 }
  	 fprintf(outp,"\n");
 }

  fclose(inp);
  fclose(outp);
  free(vocab);
  free(M);
  return 0;
}
