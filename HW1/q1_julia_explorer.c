#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc<2){
                printf("Error: bad file");
                exit(-1);
        }
	FILE* f1=fopen(argv[1],"r+");
	if(f1== NULL){
		printf("Error: bad file");
		exit(-1);
	}
	char buffer_a[10000];
	char buffer_b[10000];
	int num_a = 0;
	int num_b = 0;

	while(fgets(buffer_a,9999,f1)){
		buffer_a[strlen(buffer_a) -1] = '\0';
		if(strstr(buffer_a, "#A#")!=NULL){
            		num_a++;
        	}
	}
	fclose(f1);
	FILE* f2=fopen(argv[1],"r+");
	while(fgets(buffer_b,9999,f2)){
                buffer_b[strlen(buffer_b) -1] = '\0';
                if(strstr(buffer_b, "#B#")!=NULL){
                        num_b++;
                }
        }
 	fclose(f2);
	if(num_a == 0 || num_b == 0){
                printf("Error: bad file");
                exit(-1);
        }
	if(argc<4){
                printf("Error: bad float arg");
                exit(-1);
        }
	

	//number
	float a;
        float b;
	a=atof(argv[2]);
	b=atof(argv[3]);
	if(a == 0 && strcmp(argv[2],"0")!=0){
                printf("Error: bad float arg");
                exit(-1);
        }else if(b == 0 && strcmp(argv[3],"0")!=0){
                printf("Error: bad float arg");
                exit(-1);
        }
	char a1[32];
        char a2[32];
        sprintf(a1,"%.6f",a);
        sprintf(a2,"%.6f",b);
	
	

	//print
	int test;
	FILE* fp=fopen(argv[1],"r+");
	char c;
	while((c=fgetc(fp))!=EOF){
		char d,e;	
		if(c=='#'){
			fseek(fp,0L,SEEK_CUR);
			d=fgetc(fp);
			fseek(fp,0L,SEEK_CUR);
			e=fgetc(fp);
			if(d=='A' && e=='#'){
				printf("%s",a1);
			}else if(d=='B' && e=='#'){
                                printf("%s",a2);
                        }else{
				printf("%c%c%c",c,d,e);
			} 
			//continue;
		}else{
                        printf("%c",c);
                }
 	}
    	fclose(fp);
	return 0;
}
