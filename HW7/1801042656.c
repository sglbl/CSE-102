#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE      2001
#define NAMESIZE  200
#define GENRESIZE 20
#define ROWSIZE   200

void menu(char name[SIZE][NAMESIZE],char genre[GENRESIZE][GENRESIZE],char platform[GENRESIZE][GENRESIZE],float info[SIZE][7]){
	/*In info[][j]; if j=0 is for genre info, j=1 platform info, j=2 year, j=3 na_sales, j=4 eu_s, j=5 glob_s, j=6 score */
	int i,choice,check,check2,untilsince,count,numberofgenre,numberofplatform;
	float year,sum;
	char gamename[NAMESIZE];

	check=1;
	while(check==1){

		printf("\n0: List of the Genres \n1: List of the Platforms\n");
		printf("2: List of the Games Through the years \n3: All informations as a single game\n");
		printf("4: Average of the User Scores \n5: Geographical Information of a Single Game\n");
		printf("6: Frequency of the Genres \n7: Frequency of the Platforms\n");
		printf("8: Exit\n \nPlease select an operation: ");
		while( scanf("%d",&choice) != 1 && getchar() != '\n' )	printf("TRY AGAIN:\n");  // to prevent infinite loop.
		
		switch(choice){
			case 0:
				i=0;
				while( genre[i][0] != '\0'){
					printf("%s\n",genre[i]);
					i++;
				}
				numberofgenre=i;
				break;

			case 1:
				i=0;
				while( platform[i][0] != '\0'){
					printf("%s\n",platform[i]);
					i++;
				}
				numberofplatform=i;
				break;

			case 2:
				printf("Enter a year: ");
				while(scanf("%f",&year) != 1 && getchar() != '\n')   printf("TRY AGAIN: \n"); //Prevent infinite loop
				printf("Until(0) or Since(1) %.0f ? ",year);
				while(scanf("%d",&untilsince) != 1 && getchar() != '\n')   printf("TRY AGAIN: \n");
				while(year>info[SIZE-1][2] || year<info[1][2] || (untilsince!=0 && untilsince!=1) ){ //	Errors
					printf("\nThere aren't any release in that interval or you entered a wrong character.\n");
					printf("Enter a year: ");
					while(scanf("%f",&year) != 1 && getchar() != '\n')   printf("TRY AGAIN: \n");
					printf("Until(0) or Since(1) %.0f ? ",year);
					while(scanf("%d",&untilsince) != 1 && getchar() != '\n')   printf("TRY AGAIN: \n");
				}//End of the error messages
				if(untilsince==0){
					for(i=1; year-info[i][2] >=0.0 ;i++)
						printf("%s\n",name[i]);
				}
				else if(untilsince==1){
					for(i=1; i<SIZE ;i++)
						if(year-info[i][2] <=0.0)	 printf("%s\n",name[i]);
				}
				break;

			case 3:
				check2=0;
				while(check2==0){
					printf("Please enter the name of the game: \n");
					scanf("%s",gamename);
					for(i=1;i<SIZE;i++)
						if(strcmp(gamename,name[i])==0){
							check2=1;
							break;
						}
					if(check2==0)	printf("Wrong name. ");
				}
				printf("Name:           %s\n",name[i]);
				printf("Genre:          %s\n",   genre[ (int)info[i][0] ] );
				printf("Platform:       %s\n",platform[ (int)info[i][1] ] );
				printf("Year:           %.0f\n",info[i][2]);
				printf("Sales in NA:    %.3f\n",info[i][3]);
				printf("Sales in EU:    %.3f\n",info[i][4]);
				//if info[i][5]==0 -> which means global sales data are not_available.
				if(info[i][5]<0.001 && info[i][5]>-0.001)   printf("Total Sales:    Not Available\n");
				else if(info[i][5] > 0.0001)				printf("Total Sales:    %.3f\n",info[i][5]);
				printf("User Score:     %.3f\n",info[i][6]);
				break;

			case 4:
				sum=0;
				for(i=1;i<SIZE;i++)		sum += info[i][6];
				printf("%f\n",sum/(SIZE-1));
				break;

			case 5:
				check2=0;
				while(check2==0){
					printf("Please enter the name of the game: \n");
					scanf("%s",gamename);
					for(i=1;i<SIZE;i++)
						if(strcmp(gamename,name[i])==0){
							check2=1;
							break;
						}
					if(check2==0)	printf("Wrong name. ");
				}
				if     (info[i][3] > info[i][4])    printf("This game was more popular in North America\n");
				else if(info[i][3] < info[i][4]) 	printf("This game was more popular in Europe\n");
				else if(info[i][3]== info[i][4])    printf("This game had popularity in EU and NA\n");
				break;

			case 6:
				i=0;
				while( genre[i][0] != '\0')    i++;
				numberofgenre=i;
				for(i=0; i<numberofgenre ;i++){
					count=0;
					for(int j=1; j<SIZE ;j++)
						if( info[j][0]==i )	   count++;
					if(strlen(genre[i])>=8 )
						printf("%s\t%d\n",genre[i],count);
					else if(strlen(genre[i])<8 )
						printf("%s\t\t%d\n",genre[i],count);
				}
				break;

			case 7:
				i=0;
				while( platform[i][0] != '\0')    i++;
				numberofplatform=i;
				for(i=0; i<numberofplatform ;i++){
					count=0;
					for(int j=1; j<SIZE ;j++)
						if( info[j][1]==i )	   count++;
					/* Size of string makes difference when length is different */
						printf("%s\t%d\n", platform[i], count);
				}
				break;

			case 8:
				printf("Goodbye.\n");
				check=0;
				break;

			default:
				printf("TRY AGAIN.\n\n");
		}
	}
}


void read_file(char buffer[SIZE][ROWSIZE] ){

	char name[SIZE][NAMESIZE], allgenres[SIZE][GENRESIZE], allplatforms[SIZE][GENRESIZE];
	char genreBuffer[GENRESIZE][GENRESIZE], platBuffer[GENRESIZE][GENRESIZE], unnecessarybuf[GENRESIZE];
	int i,j,k,p,flag;
	
	float info[SIZE][7];
	/*In info[][j]; if j=0 is for genre info, j=1 platform info, j=2 year, j=3 na_sales, j=4 eu_s, j=5 glob_s, j=6 score */
	FILE *filep=fopen("Video_Games.txt","r+");
	if(filep==NULL){
		printf("Couldn't read file.");
		return;
	}

	i=0,k=0;
	while( i<SIZE ){
		fgets(buffer[i],SIZE,filep);
		buffer[i][ strlen(buffer[i]) ] = '\0';
		/* It will read strings until comma character - Separating strings with comma */
		sscanf(buffer[i],"%[^,],%[^,],%[^,],%f,%f,%f,%f,%f",name[i],allgenres[i],allplatforms[i],
									&info[i][2],&info[i][3],&info[i][4],&info[i][5],&info[i][6]);
		if(info[i][5]< 0.0001 && info[i][5]> -0.0001){  //which means global sales data are not_available.
			sscanf(buffer[i],"%[^,],%[^,],%[^,],%f,%f,%f,%[^,],%f",name[i],allgenres[i],allplatforms[i],
										&info[i][2],&info[i][3],&info[i][4],unnecessarybuf,&info[i][6]);
		}	

		i++;
	}
	fclose(filep);

	p=0;
	for(int m=1;m<SIZE;m++){
		flag=1;
		for(int n=0;n<GENRESIZE;n++)
			if( strcmp( genreBuffer[n],allgenres[m])==0 )	flag=0;	
		if(flag==1){
			strcpy(genreBuffer[p],allgenres[m] );  
			p++;
		}
	}	
	for(int m=1;m<SIZE;m++)
		for(int n=0;n<GENRESIZE;n++) 		//i.e. if genreBuffer[p]="simulation", p number in float will show "simulation"
			if( strcmp( genreBuffer[n],allgenres[m])==0 )	info[m][0]=n;
	/*Now every genre name has a value */

	p=0;
	for(int m=1;m<SIZE;m++){
		flag=1;
		for(int n=0;n<GENRESIZE;n++)
			if( strcmp( platBuffer[n],allplatforms[m])==0 )	flag=0;	
		if(flag==1){
			strcpy(platBuffer[p],allplatforms[m] ); 
			p++;
		}
	}	
	for(int m=1;m<SIZE;m++)
		for(int n=0;n<GENRESIZE;n++)		//i.e. if platBuffer[p]="pc", p number in float will show "pc"
			if( strcmp( platBuffer[n],allplatforms[m])==0 )	info[m][1]=n;		
	/*Now every platform name has a value */

	menu(name, genreBuffer, platBuffer, info);
}

int main(){
	char buffer[SIZE][ROWSIZE];
	read_file(buffer);
	return 0;
}