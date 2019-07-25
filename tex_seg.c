/*********************************************************************************
**********************************************************************************
This program culcrate.
arguments are vector binary data, input file, output file, and number of words as lines.
**********************************************************************************
*********************************************************************************/

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
  char inpf_name[max_size], outpf_name[max_size], file_name[max_size];//file_nameは引数のargvを格納する配列
  float len;
  long long words, size, a, b, c, d, cn, i;//wordsはバイナリファイルに登録してある単語の数,sizeは各分散ベクトルの次元数
  float *M;//*Mは概念行列を格納するポインタ
  char *vocab;
  long long lines;
  float ave_w[200] = {0}, tmp_w[200] = {0}, A[200] = {0};



  //confirmation of argument
  if (argc < 2) {
    printf("Misstake about argument.\n");
    return 0;
  }


  //open file and error check
  strcpy(file_name, argv[1]);
  dicf = fopen(file_name, "rb");
  if (dicf == NULL) {
    printf("Binary file not found\n");
    return -1;
  }
  
  strcpy(inpf_name, argv[2]);
  inp = fopen(inpf_name, "r");
  if (inp == NULL) {
    printf("Input file not found\n");
    return -1;
  }

  strcpy(outpf_name,argv[3]);
  outp = fopen(outpf_name, "w");
  if (outp== NULL) {
    printf("Output file not found\n");
    return -1;
  }

  lines = atoi(argv[4]);

  size=200;
  

  //Reserve memory for Co-occurense matrix
  vocab = (char *)malloc((long long)lines * max_w * sizeof(char));     

  M = (float *)malloc((long long)lines * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;

  }

  //Put in data to input file.
  for(b=0;b<lines;b++){
		  fscanf(dicf,"%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,",&vocab[b*max_w*sizeof(char)],&M[0+b*size],&M[1+b*size],&M[2+b*size],&M[3+b*size],&M[4+b*size],&M[5+b*size],&M[6+b*size],&M[7+b*size],&M[8+b*size],&M[9+b*size],&M[10+b*size],&M[11+b*size],&M[12+b*size],&M[13+b*size],&M[14+b*size],&M[15+b*size],&M[16+b*size],&M[17+b*size],&M[18+b*size],&M[19+b*size],&M[20+b*size],&M[21+b*size],&M[22+b*size],&M[23+b*size],&M[24+b*size],&M[25+b*size],&M[26+b*size],&M[27+b*size],&M[28+b*size],&M[29+b*size],&M[30+b*size],&M[31+b*size],&M[32+b*size],&M[33+b*size],&M[34+b*size],&M[35+b*size],&M[36+b*size],&M[37+b*size],&M[38+b*size],&M[39+b*size],&M[40+b*size],&M[41+b*size],&M[42+b*size],&M[43+b*size],&M[44+b*size],&M[45+b*size],&M[46+b*size],&M[47+b*size],&M[48+b*size],&M[49+b*size],&M[50+b*size],&M[51+b*size],&M[52+b*size],&M[53+b*size],&M[54+b*size],&M[55+b*size],&M[56+b*size],&M[57+b*size],&M[58+b*size],&M[59+b*size],&M[60+b*size],&M[61+b*size],&M[62+b*size],&M[63+b*size],&M[64+b*size],&M[65+b*size],&M[66+b*size],&M[67+b*size],&M[68+b*size],&M[69+b*size],&M[70+b*size],&M[71+b*size],&M[72+b*size],&M[73+b*size],&M[74+b*size],&M[75+b*size],&M[76+b*size],&M[77+b*size],&M[78+b*size],&M[79+b*size],&M[80+b*size],&M[81+b*size],&M[82+b*size],&M[83+b*size],&M[84+b*size],&M[85+b*size],&M[86+b*size],&M[87+b*size],&M[88+b*size],&M[89+b*size],&M[90+b*size],&M[91+b*size],&M[92+b*size],&M[93+b*size],&M[94+b*size],&M[95+b*size],&M[96+b*size],&M[97+b*size],&M[98+b*size],&M[99+b*size],&M[100+b*size],&M[101+b*size],&M[102+b*size],&M[103+b*size],&M[104+b*size],&M[105+b*size],&M[106+b*size],&M[107+b*size],&M[108+b*size],&M[109+b*size],&M[110+b*size],&M[111+b*size],&M[112+b*size],&M[113+b*size],&M[114+b*size],&M[115+b*size],&M[116+b*size],&M[117+b*size],&M[118+b*size],&M[119+b*size],&M[120+b*size],&M[121+b*size],&M[122+b*size],&M[123+b*size],&M[124+b*size],&M[125+b*size],&M[126+b*size],&M[127+b*size],&M[128+b*size],&M[129+b*size],&M[130+b*size],&M[131+b*size],&M[132+b*size],&M[133+b*size],&M[134+b*size],&M[135+b*size],&M[136+b*size],&M[137+b*size],&M[138+b*size],&M[139+b*size],&M[140+b*size],&M[141+b*size],&M[142+b*size],&M[143+b*size],&M[144+b*size],&M[145+b*size],&M[146+b*size],&M[147+b*size],&M[148+b*size],&M[149+b*size],&M[150+b*size],&M[151+b*size],&M[152+b*size],&M[153+b*size],&M[154+b*size],&M[155+b*size],&M[156+b*size],&M[157+b*size],&M[158+b*size],&M[159+b*size],&M[160+b*size],&M[161+b*size],&M[162+b*size],&M[163+b*size],&M[164+b*size],&M[165+b*size],&M[166+b*size],&M[167+b*size],&M[168+b*size],&M[169+b*size],&M[170+b*size],&M[171+b*size],&M[172+b*size],&M[173+b*size],&M[174+b*size],&M[175+b*size],&M[176+b*size],&M[177+b*size],&M[178+b*size],&M[179+b*size],&M[180+b*size],&M[181+b*size],&M[182+b*size],&M[183+b*size],&M[184+b*size],&M[185+b*size],&M[186+b*size],&M[187+b*size],&M[188+b*size],&M[189+b*size],&M[190+b*size],&M[191+b*size],&M[192+b*size],&M[193+b*size],&M[194+b*size],&M[195+b*size],&M[196+b*size],&M[197+b*size],&M[198+b*size],&M[199+b*size]);
		  }



/*
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
*/

  fclose(dicf);
  


/*
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
   	 //Put out distrebuted representation to output file.
	 a=0;
  	 while(st1[a]!=0){
   		fprintf(outp,"%c",st1[a]);
		printf("%c",st1[a]);
		a++;
  	 }
	 puts("");
  	 fprintf(outp,",");
  	 for(a=0;a<size;a++){
   		fprintf(outp,"%.5f,",M[a+b*size]);
		printf("%.5f",M[a+b*size]);
		ave_w[a] += (M[a+b*size]);
  	 }
  	 fprintf(outp,"\n");
 }
*/




  //Culcurate w.
  printf("---------------------------------------------------------------------------------------------------------------------------------------------\n---------------------------------------------------------------------------------------------------------------------------------------------\n printf ave_w         \n");
  for(a=0;a<size;a++){
	  printf("%0.4f     ",ave_w[a]/size);
	  if(a%9 == 0){
	  	printf("\n");
          }
  }

  //Clucrate A.
  printf("---------------------------------------------------------------------------------------------------------------------------------------------\n---------------------------------------------------------------------------------------------------------------------------------------------\n printf A         \n");
  for(b=0;b<lines;b++){
	  for(a=0;a<size;a++){
		 printf("%0.4f",A[a] += pow(fabsf(M[a+b*size]-(ave_w[a]/size)),2.0));
	  }
  }



  fclose(inp);
  fclose(outp);
  free(vocab);
  free(M);
  return 0;
}
