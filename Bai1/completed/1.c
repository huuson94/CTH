#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define POS_MAX 100
#define WORD_MAX 1000
#define ARRAY_MAX 1000

typedef struct{
	char text[WORD_MAX];
	int count	;//so luong tu
	char pos[POS_MAX]; //vi tri
}word;


int isStopW(char *s);
void docTu(char *fileName, word a[], char b[][WORD_MAX], int *j, int *d);
int kiemTra(word coNghia[], int *d, int e, char *str);
void sortArray(word coNghia[], int d);

/**
kiem tra neu co str trong word[] thi tang count ,  nguoc lai count =1
d la bien tong so tu trong mang coNghia, e la bien so dong xuat hien cua str
*/
int kiemTra(word coNghia[], int *d, int e1, char *str){ 

	int i ;
	int k = 0;
	char temp[WORD_MAX];
//	printf("4.%s\n", str);
	for(i = 0; i < (*d); i++){/*Neu tu da co trong danh sach thi tang count va them pos*/
		if(strcmp(str, (coNghia[i].text)) == 0) {
			(coNghia[i].count) ++;
			sprintf(temp,", %d",e1);
			strcat(coNghia[i].pos, temp);
			k = 1;
		}
	}
	if(k == 0) {    /*Neu str chua ton tai trong danh sach*/
	// 	printf("5.%s\n", str);
		strcpy((coNghia[(*d)++].text),str);
		sprintf(temp," %d",e1);
		strcat(coNghia[i].pos, temp);
		coNghia[i].count =1;

	}
}


int isDTR(char *str){
	FILE *fOpen = fopen("vanban.txt","r");
	char *line;
	while(1){
		fgets(line, 100, fOpen);
		if(feof(fOpen) == 1) break;
		else{

			line = strstr(line,str);
		}
	}

	fclose(fOpen);
}

int isStopW(char *s){
	FILE *fOpen = fopen("stopw.txt","r");
	if(fOpen == NULL) {
		printf("Khong tim thay file stopw.txt");
		exit(0);
	}
	char str[WORD_MAX];
	char c;
	int i=0;
	int t;
	while(1){
		c=fgetc(fOpen);
		if(feof(fOpen) == 1){
			break;
		}
		else{
			if( (c > 64 && c < 91) || (c > 96 && c < 123)){
				str[i++] = c;
			}
			else{
				if(i> 0){
					str[i]='\0';
					if(strcmp(str,s) == 0){
						t=1;
						break;
					}
					else t = 0;
				}
				
				i=0;
			}
		}
	}
	fclose(fOpen);

	return t;
}

void docTu(char *fileName, word coNghia[], char voNghia[][WORD_MAX], int *d, int *e){
	FILE *fOpen = fopen(fileName,"r");
	if(fOpen == NULL) {
		printf("Khong tim thay file %s", fileName);
		exit(0);
	}
	
	char temp[WORD_MAX];
	char c, t; /*c la bien ki tu tam thoi, t la de luu dau '.'*/
	int i = 0;
	int e1=1; /*dem so dong xuat hien cua tu*/
	//int d=0; //dem coNghia
	int k = 0, h=0; //dem dau '.'
	int beCheck;
	while(1){
		c=fgetc(fOpen);
		

		if(feof(fOpen) == 1){
			return;
		}
		else{

			if( (c > 64 && c < 91) || (c > 96 && c < 123)){
				if((c > 64) && (c < 91)) {
					temp[i++] = c +32;
					beCheck =1;/*co kiem tra la DTR hay khong*/
				}
				else temp[i++] = c;
			}
			else{ /*quet duoc ki tu la*/
				/*Neu ki tu la la \n thi tang e len 1*/
				if(c == '\n' ) e1++;
				if( i > 0) {
					temp[i]='\0';
				//	printf("1.%s\n",temp);
				//	d++;
					if(isStopW(temp) == 1){/*temp co mat trong stopw.txt*/
				//		printf("Trung trong stopw.txt=>Loai\n");
						strcpy(&(voNghia[(*e)++][WORD_MAX]), temp);
					//	printf("%s\n", temp);
					}
					else if(beCheck == 1){ /*kiem tra neu nhu tu bat dau bang ki tu hoa va khong phai la tu dau doan van.*/
					//	kiem tra la DTK
					//	printf("2.%s\n", temp);	
					
						beCheck = 0;
					}
					else {
					// 	printf("3.%s\n", temp);
						kiemTra(coNghia, d, e1, temp);
						
					}
				}
				i = 0;
				beCheck = 0;
			}

		}
	}

	fclose(fOpen);
}

void sortArray(word coNghia[], int d){/*Cach sap xep nay co do lon cao, can toi uu*/
	word toEx;
	int i, j;
	for(i = 0; i < d; i++){
		for(j = 0; j < d-1; j++){
			if(strcmp(coNghia[j+1].text, coNghia[j].text) < 0){
				toEx = coNghia[j+1];
				coNghia[j+1] = coNghia[j];
				coNghia[j] = toEx;
			}
		}
	}
	
}
main(){
	word coNghia[ARRAY_MAX];
	char voNghia[ARRAY_MAX][WORD_MAX];
	int e = 0, d = 0; /* d la tong so coNghia, e la tong vo Nghia*/
	int i = 0,j = 0;
	docTu("vanban.txt", coNghia,voNghia, &d , &e);
	sortArray(coNghia, d);
	printf("%-10s\t%-4s\t%-10s\n","Word","Count","Position");
	printf("_____________________________\n");
	
	for(i = 0; i < d; i++){
		printf("%-10s\t%-4d\t%-10s\n", coNghia[i].text,coNghia[i].count,coNghia[i].pos);
	}
	printf("Danh sach vo nghia\n______________________\n______________________\n");
	for(i = 0; i < e; i++){
		printf("%10s\n",voNghia[i]);
	}

}