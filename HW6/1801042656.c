#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define  ROW    20
#define  COLUMN 20
#define  LENGTH 13
#define  WORDS  100
#define  MAXSIZE 19
#define  LISTWORD 10

char make_capital(char letter){
    letter -= 32;	//To the ascii 
	return letter;
}

void make_capital_in_grid(char wordlist[LISTWORD][LENGTH],char grid[ROW][COLUMN],int letterrow, int numcolumn,int buf){
	int a=0;
	int size=strlen(wordlist[buf])-2;
	for(int j=1; j<size-1 ;j++){
		if( wordlist[buf][j]==grid[letterrow][numcolumn+j] -32)       a=1;//buf value is capital letter value. So difference must be 32.
		else if( wordlist[buf][j]==grid[letterrow][numcolumn-j] -32)  a=2;
		else if( wordlist[buf][j]==grid[letterrow+j][numcolumn] -32)  a=3;
		else if( wordlist[buf][j]==grid[letterrow-j][numcolumn] -32)  a=4;
		else if( wordlist[buf][j]==grid[letterrow+j][numcolumn+j]-32) a=5;
		else if( wordlist[buf][j]==grid[letterrow-j][numcolumn-j]-32) a=6;
		else if( wordlist[buf][j]==grid[letterrow+j][numcolumn-j]-32) a=7;
		else if( wordlist[buf][j]==grid[letterrow-j][numcolumn+j]-32) a=8;
	}
		
	switch(a){
		case 1:			//If word is in horizontal direction
			for(int j=0;j<size;j++)
				grid[letterrow][numcolumn+j]=make_capital(grid[letterrow][numcolumn+j]);
			break;  
		case 2:			//If word is in reverse-horizontal direction
			for(int j=0;j<size;j++)
				grid[letterrow][numcolumn-j]=make_capital(grid[letterrow][numcolumn-j]);
			break;
		case 3:			//If word is in vertical direction
			for(int j=0;j<size;j++)
				grid[letterrow+j][numcolumn]=make_capital(grid[letterrow+j][numcolumn]);
			break;
		case 4:			//If word is in reverse-vertical direction
			for(int j=0;j<size;j++)
				grid[letterrow-j][numcolumn]=make_capital(grid[letterrow-j][numcolumn]);
			break;
		case 5:			//If word is in diagonal direction  (Left cross direction)
			for(int j=0;j<size;j++)
				grid[letterrow+j][numcolumn+j]=make_capital(grid[letterrow+j][numcolumn+j]);
			break;
		case 6:			//If word is in reverse-diagonal direction  (Left cross)
			for(int j=0;j<size;j++)
				grid[letterrow-j][numcolumn-j]=make_capital(grid[letterrow-j][numcolumn-j]);
			break;
		case 7:			//If word is in other diagonal direction (Right cross direction)
			for(int j=0;j<size;j++)
				grid[letterrow+j][numcolumn-j]=make_capital(grid[letterrow+j][numcolumn-j]);
			break;
		case 8:			//If word is in other reverse-diagonal direction (Right cross)
			for(int j=0;j<size;j++)
				grid[letterrow-j][numcolumn+j]=make_capital(grid[letterrow-j][numcolumn+j]);
			break;
		default:  
			printf("Error\n");
	}	
}

void grid_printing(char grid[ROW][COLUMN]){
	//If you add a /* to here, random words won't be generated, just words could be seen.
	/*for(int i=0;i<ROW;i++)				//Random letter generator
		for(int j=0; j<COLUMN ;j++)
			if(grid[i][j] == '*')	//If point is empty
				grid[i][j]=(char)('a' + (random() % 26));  /*from ascii table*/

	printf("   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19\n");
	for(int i=0; i<ROW ;i++){
		printf("%c  ",i+'A');
		for(int j=0; j<COLUMN ;j++ )	printf("%c  ",grid[i][j]);	
		printf("\n");
	}
}
void enter_input(char wordlist[LISTWORD][LENGTH], char locy[LISTWORD], int locx[LISTWORD], char grid[ROW][COLUMN]){
	int  i,numberloc,flag,buf,check,size,countword;
	char c,letterloc, string[LENGTH],input[LENGTH+1];

	check=1, countword=0;
	while(check==1){
		grid_printing(grid);
		printf("\nSelected word list:\n");
		for(int i=0; i<LISTWORD ;i++)
			printf("%s",wordlist[i]);
		printf("Enter coordinates and word:"); //After first scanf, users don't have to click enter.
	
		scanf(" %13[^\n]",input);   //less than input size
		if( strncmp(input,"Exit",4)==0 ){   //read the first 4 char.
			printf("Program is terminating.\n");
			return;
		}
		sscanf(input,"%c%d%s",&letterloc,&numberloc, string);

		flag=1, buf=-1;
		for(i=0; i<LISTWORD ;i++)
			if( locx[i]==numberloc && locy[i]==letterloc )	
				buf=i;		
		if(buf == -1){
			printf("!!Wrong input1!!\n");
			continue;
		}
		//If process reaches here, then there is a match in location.
		size=strlen(wordlist[buf])-2; 
		for(i=0;i<size;i++) 
			if(string[i] != wordlist[buf][i])
				flag=0;
		if(flag == 0){
			printf("!!Wrong input2!!\n");
			continue;
		}
		//If process reaches here, then there is a match in word && location.
		for(i=0;i<size;i++)
			wordlist[buf][i]=make_capital( wordlist[buf][i] );//Making uppercase in list.
		make_capital_in_grid(wordlist,grid,letterloc-65, numberloc,buf);//Making uppercase in grid board.
		countword++;
		printf("%d %s",countword,wordlist[buf]);
		if(countword== LISTWORD ){
			grid_printing(grid);
			for(int i=0;i< LISTWORD ;i++)
				printf("%s",wordlist[i]);
			printf("Congratulations.\n");
			check=0;
			break;
		}

	}
}
	/* is_empty function will check if grid[randomy][randomx] is empty and it checks if word shifts to other side */
int is_empty(int randomx,int randomy, int size,int which, char grid[ROW][COLUMN] ){
	int emptiness=1;
	/*  If  grid[randomy][randomx]='*' , than it means it is an empty cell   */
	switch(which){
		case 1:
			for(int m=0;m<size;m++)
				if (grid[randomy][randomx+m]!='*' || (randomx+size> MAXSIZE) ){ //if field is not empty and there is no shift
					emptiness=0;
					break;
				}
			break;
		case 2:
			for(int m=size; m>0 ;m--)
				if (grid[randomy][randomx+m]!='*' || (randomx+size> MAXSIZE) ){ 
					emptiness=0;
					break;
				}
			break;
		case 3:
			for(int m=0;m<size;m++)
				if (grid[randomy+m][randomx]!='*' || (randomy+size> MAXSIZE) ){ 
					emptiness=0;
					break;
				}
			break;
		case 4:
			for(int m=size; m>0 ;m--)
				if (grid[randomy+m][randomx]!='*' || (randomy+size> MAXSIZE) ){ 
					emptiness=0;
					break;
				}
			break;
		case 5:
			for(int m=0;m<size;m++)
				if (grid[randomy+m][randomx+m]!='*' || (randomx+size> MAXSIZE) || (randomy+size>MAXSIZE) ){ 
					emptiness=0;
					break;
				}
			break;
		case 6:
			for(int m=size; m>0 ;m--)
				if (grid[randomy+m][randomx+m]!='*' || (randomx+size> MAXSIZE) || (randomy+size>MAXSIZE) ){ 
					emptiness=0;
					break;
				}
			break;
		case 7:
			for(int m=0;m<size;m++)
				if (grid[randomy+m][randomx-m]!='*' || (randomy+size> MAXSIZE) || (randomx-size<0) ){ 
					emptiness=0;
					break;
				}
			break;
		case 8:
			for(int m=size; m>0 ;m--)
				if (grid[randomy+m][randomx-m]!='*' || (randomy+size> MAXSIZE) || (randomx-size<0) ){ 
					emptiness=0;
					break;
				}
			break;
	}	
	return emptiness;	
}

void process(char buffer[WORDS+1][LENGTH] ){ 
	char grid[ROW][COLUMN],randletter; // randletter will generate a random number
	char words[LISTWORD][LENGTH],wordlocationsY[LISTWORD]; //words will be used to store words(Second one'll be used to store y locations of words)
	int  wordlocationsX[LISTWORD];	  // it will be used to store x locations of words
	int  n,size,letterorword,randword,which,countword;
	int  randomx,randomy;
	srand(time(NULL));

	for(int i=0;i<ROW;i++)
		for(int j=0; j<COLUMN ;j++ )	
			grid[i][j]='*';	
	
	countword=0;
	for(int i=0;i<ROW;i++){
		for(int j=0; j<COLUMN ;j++ ){ 
			randomx=rand()%COLUMN;
			randomy=rand()%ROW;
			randword=rand()%WORDS;		//randword will be between 0 and 99
			size=strlen( buffer[randword] )-2;
			if(randword==(WORDS-1))	size=strlen(buffer[randword])-1; /*because of this was the last line in the file,
			                                                 string length is different from the other word lines in file*/
			if( grid[randomy][randomx] != '*' || countword>=LISTWORD )  continue; //not empty
			countword++;
			which=rand()%8+1;
				switch(which){
					case 1://Print horizontal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)randomy + 'A' ;
						wordlocationsX[countword-1] = randomx;
						for(n=0; n<size ;n++)
							grid[randomy][randomx+n]=buffer[randword][n];
						break;

					case 2://Print reverse-horizontal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						n=size;
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)randomy + 'A' ;
						wordlocationsX[countword-1] = randomx + n;
						for(n=size; n>0  ;n--)
							grid[randomy][randomx+n]=buffer[randword][size-n];
						break;

					case 3://Print vertical direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)randomy + 'A' ;
						wordlocationsX[countword-1] = randomx;
						for(n=0; n<size ;n++)
							grid[randomy+n][randomx]=buffer[randword][n];
						break;

					case 4://Print reverse-vertical direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						n=size;
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)(randomy+size) + 'A' ;
						wordlocationsX[countword-1] = randomx;
						for(n=size; n>0  ;n--)
							grid[randomy+n][randomx]=buffer[randword][size-n];
						break;

					case 5://Print diagonal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)randomy + 'A' ;
						wordlocationsX[countword-1] = randomx;
						for(n=0; n<size ;n++)
							grid[randomy+n][randomx+n]=buffer[randword][n];
						break;

					case 6://Print reverse-diagonal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						n=size;
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)(randomy+n) + 'A' ;
						wordlocationsX[countword-1] = randomx + n;
						for(n=size; n>0  ;n--)
							grid[randomy+n][randomx+n]=buffer[randword][size-n];
						break;

					case 7://Print other diagonal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)randomy + 'A' ;
						wordlocationsX[countword-1] = randomx;
						for(n=0; n<size ;n++)
							grid[randomy+n][randomx-n]=buffer[randword][n];
						break;

					case 8://Print reverse-diagonal direction
						if(is_empty(randomx,randomy,size,which,grid)==0){ //means it's not empty.
							countword--;
							break;
						}
						n=size;
						strcpy(words[countword-1],buffer[randword]);
						wordlocationsY[countword-1] = (char)(randomy + n) + 'A' ;
						wordlocationsX[countword-1] = randomx - n;
						for(n=size; n>0  ;n--)
							grid[randomy+n][randomx-n]=buffer[randword][size-n];
						break;
				}
		}
	}
	enter_input(words,wordlocationsY,wordlocationsX,grid);
}
	/*This function will send everything in file to a buffer */
void read_from_file(char* file_path,char buffer[WORDS+1][LENGTH]){
	int i,j;
	FILE *filep=fopen(file_path,"r");
	if(filep==NULL){
	    printf("File couldn't open.");
	    return;
	}
	for(i=0; i<WORDS; i++){
		fgets(buffer[i], LENGTH+1 ,filep);
		if(i==WORDS-1)	buffer[i][strlen(buffer[i])]='\n';	//For the last word.
	    buffer[i][strlen(buffer[i])+2] = '\0';
	}
	fclose(filep);
	process(buffer);
}

int main(){
	char buffer[WORDS+1][LENGTH];
	read_from_file("words.txt",buffer);
	return 0;
}