#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#define j 10000

const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

int main(int argc, char *argv[]) {
  FILE *dicf,*inp,*outp;//バイナリファイルを読み込むストリーム
  char st1[max_size],stf[50];//I made stf[] for get a word from Wakatidate*.txt
  char *bestw[N];//コサイン距離が近い単語N個を格納する配列
  char file_name[max_size], st[100][max_size];//file_nameは引数のargvを格納する配列
  float dist, len, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100],i;//wordsはバイナリファイルに登録してある単語の数,sizeは各分散ベクトルの次元数
  char ch;
  float *M,test[j];//*Mは概念行列を格納するポインタ
  char *vocab;



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
  
  inp = fopen("data/article_f_samp_waka_fil.svd", "r");
  if (inp == NULL) {
    printf("Input file not found\n");
    return -1;
  }

  outp = fopen("data/article_samp_desrep.cvd", "w");
  if (outp== NULL) {
    printf("Output file not found\n");
    return -1;
  }


  words=4536628;
  size=200;
  

  //Reserve memory for Co-occurense matrix
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));    //bestw[] may be an array for candidate of nearest words. 

  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));

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
     		 vocab[b * max_w + a] = fgetc(f);
     		 if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
     		 if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
    	}
   	vocab[b * max_w + a] = 0;
	//Put in number to M[].
   	for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);

    	//Normaliz M[]'s number.
    	len = 0;
    	for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    	len = sqrt(len);
   	for (a = 0; a < size; a++) M[a + b * size] /= len;
  }


  fclose(dicf);
  
  while (fgets(stf,50,inp)!=NULL) {
    	a = 0;
  	 //----------------------ユーザが打った単語をst配列に格納している。最後に0を代入している。------------------
  	 while (1) {
     		 st1[a] = stf[a];
     		 if ((st1[a] == '\n') || (a >= max_size - 1)) {
       			 st1[a] = 0;
      			  break;
      		}
     		 a++;
   	 }
   //----------------------フレーズを入力された場合に単語に分解している。-------------------
    if (!strcmp(st1, "EXIT")) break;

    
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
   //********************打ち込まれた単語を辞書内から検索している。**********************
    for (a = 0; a < cn; a++) {
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      
      if (b == words) b = -1;
      bi[a] = b;
      printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);

      ///error that the target word does not appear in the dictionaly
      if (b == -1) {
        printf("Out of dictionary word!\n");
        break;
      }
    }
    //------------------------------------------------------------------------------------
    if (b == -1) continue;

   printf("word: %s",st[a]);
   for(a=0;a<size;a++){
	if(a%10==0)	printf("\n%lld:::",(a/10)+1);
	printf("%.4f	",M[a + b * size]);
   }

   a=0;
   while(st1[a]!=0){
   	fprintf(outp,"%c",st1[a]);
	a++;
   }
   fprintf(outp,",");
   for(a=0;a<size;a++){
   	fprintf(outp,"%.5f,",M[a+b*size]);
   }
   fprintf(outp,"\n");
   printf("\n");

  }


  fclose(inp);
  fclose(outp);
  free(vocab);
  for(a = 0;a < N;a++) free(bestw[a]);
  free(M);
  return 0;
}
