#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void separator(int daysize){
        printf("\n");
        printf("|");
        int i;
        for(i=0;i<(daysize+3)*7-1;i++){
                printf("-");
        }
        printf("|");
}
void month_title(int daysize,char month[]){
	int l = strlen(month);
	int i;
	printf("\n|");
	for(i=0;i<(((daysize+3)*7-1)-l)/2;i++){
		printf(" ");
	}
	printf("%s",month);
	for(i=0;i<(((daysize+3)*7-1)-l)/2;i++){
                printf(" ");
        }
	if(l%2==1 && ((daysize+3)*7-1)%2==0){
		printf(" ");
	}else if(l%2==0 && ((daysize+3)*7-1)%2==1){
                printf(" ");
        }
	printf("|");
}
void day_lable(int daysize){
	const char* day[7];
	day[1] = "Monday                                                                                                                                              ";
	day[2] = "Tuesday                                                                                                                                             ";
	day[3] = "Wednesday                                                                                                                                           ";
	day[4] = "Thursday                                                                                                                                            ";
	day[5] = "Friday                                                                                                                                              ";
	day[6] = "Saturday                                                                                                                                            ";
	day[0] = "Sunday                                                                                                                                              ";
	printf("\n|");
	int i,j;
	for (i=0;i<7;i++){
		printf(" ");
		for (j=0;j<daysize;j++){
			printf("%c",day[i][j]);
		}
		printf(" |");	
	}
}
void day_in_month(int daysize, int firstday, char month[]){
	if(strcmp(month,"January")){
		separator(daysize);
	}else{
		printf("|");
        	int i;
        	for(i=0;i<(daysize+3)*7-1;i++){
                	printf("-");
        	}
        	printf("|");
	}
	month_title(daysize,month);
	separator(daysize);
	day_lable(daysize);
	separator(daysize);
	printf("\n|");
	int i,j;
	for(i=0;i<firstday-1;i++){
		for(j=0;j<daysize+2;j++){
			printf(" ");
		}
		printf("|");
	}
	int k = firstday;
	for(j=1;j<=30;j++){
		printf(" %d",j);
		if(j-10>=0){
			int n;
			for(n=0;n<daysize-1;n++){
				printf(" ");
			}
			printf("|");
		}else if(j<10){
			int n;
                        for(n=0;n<daysize;n++){
                                printf(" ");
                        }
                        printf("|");
		}
		if(k%7==0 && j!=30){
			printf("\n|");
		}
		k++;
	}
	int m,n;
	for(m=0;(k+m-1)%7!=0;m++){
		for(n=0;n<daysize+2;n++){
                        printf(" ");
                }
                printf("|");
	}
}

int main(int argc, char* argv[]){
	int daysize = atoi(argv[1]);
	int firstday = atoi(argv[2]);
	if(daysize<2){
		printf("ERROR: Cannot print days smaller than size 2.");
		exit(-1);
	}
	if(firstday<1 || firstday>7){
                printf("ERROR: The first day of the week must be between 1 and 7.");
		exit(-1);
        }
	char* month[12];
	month[0] = "January";
        month[1] = "February";                                                                                                                                              	month[2] = "March";                                                                                                                                           
        month[3] = "April";
        month[4] = "May";                                                                                                                                         
        month[5] = "June";                                                                                                                                            
        month[6] = "July";
	month[7] = "August";
	month[8] = "September";
	month[9] = "October";
	month[10] = "November";
	month[11] = "December";
	int i;
	for(i=0; i<12; i++){
		if((firstday+2*i)%7 == 0){
			day_in_month(daysize,7,month[i]);
		}else{
			day_in_month(daysize,(firstday+2*i)%7 ,month[i]);
		}
	}
	separator(daysize);
	printf("\n");
        return 0;
}
