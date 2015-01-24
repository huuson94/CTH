#include <stdio.h>
#include <string.h>

int isStopW(char *s);
char** docTu();

int isStopW(char *s){
	FILE *fOpen = fopen("stopw.txt","r");
	if(fOpen == NULL) {
		printf("Khong tim thay file stopw.txt");
		exit(0);
	}
	char str[256];
	char c;
	int i=0;
	int t;
	while(1){
		c=fgetc(fOpen);
		if(feof(fOpen) == 1){
			break;
		}
		else{
			
		}
	}
	fclose(fOpen);

	return t;
}

char** docTu(char *fileName){
	FILE *fOpen = fopen(fileName,"r");
	if(fOpen == NULL) {
		printf("Khong tim thay file %s", fileName);
		exit(0);
	}
	char* kq[256];
	char line[100];
	char str[100];
	char c;
	int i = 0;
	int j=0;
	int isDTR = 0;
	while(1){
		
		if(feof(fOpen) == 1){
			return;
		}
		else{
			fgets(line, 100, fOpen);
			printf("%s\n", line);

		}
	}

	fclose(fOpen);
}
main(){
	docTu("vanban.txt");
	
}