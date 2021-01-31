#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
		/* 	PART1	*/
char decrypt_numbers (int number){
	switch(number){
		case 0:
			return ' ';
		case 1:
			return '-';
		case 2:
			return '_';
		case 3:
			return '|';
		case 4:
			return '/';
		case 5:
			return '\\';
		case 6:
			return 'O';
		default:
			return '\n';
	}
}

void decrypt_and_print (char* file_path){
	char buffer;
	int check,number_in_file;
	FILE *filep= fopen(file_path,"r");
	
	if (filep == NULL){
        printf("Couldn't open file\n");
        return;
    }
    check=fscanf(filep,"%c",&buffer);

    while(check != EOF ){
    	/* Taking number as character and then converting it to integer(doing it what if buffer is '\n' )  */
		check=fscanf(filep,"%c",&buffer);		
		number_in_file=(int)buffer-48;
		printf("%c",decrypt_numbers(number_in_file));
	}

	fclose(filep);	
}
		/*		PART2 */
void deep_decrypt_and_print(char* file_path){
	char buffer,buffer2,buffer3;
	int check,number_i_j=0,count=0;
	FILE *filep= fopen(file_path,"r");
	if(filep==NULL){
		printf("COuldn't open file.");
		return;
	}
	/* Taking 3 characters to store these in memory without using arrays */	
	check=fscanf(filep,"%c",&buffer);
	fscanf(filep,"%c",&buffer);
	buffer2=buffer;
	fscanf(filep,"%c",&buffer);
	buffer3=buffer;
		
	while(check != EOF){	//exit loop while we reach End of File.

		number_i_j=0;
		if(count != 0){
			buffer2=buffer3;
			buffer3=buffer;
		}
		count++;

		check=fscanf(filep,"%c",&buffer);
		
		number_i_j = (int)buffer + (int)buffer2 + (int)buffer3 -48*3;

			if(buffer=='\n'){	// I need to store 3 values like it is beginning of file (because of new line)
				fscanf(filep,"%c",&buffer);
				buffer2=buffer;
				fscanf(filep,"%c",&buffer);
				buffer3=buffer;
				fscanf(filep,"%c",&buffer);
			}   
		
		number_i_j = number_i_j % 7;
		printf("%c",decrypt_numbers(number_i_j));
		
	}
	fclose(filep);
}
		/*		PART3		*/
void refresh_position (int *X, int *Y, double *D, double *R){
	/*  *X and *Y represents position of enemy, because our location is always (6,6) */
	srand(time(NULL));
	int enLOC_x=rand()%10+1;
    int enLOC_y=rand()%10+1;

    X=&enLOC_x;
    Y=&enLOC_y;
   	/*Printing the field*/
	for(int i=1;i<11;i++){
		for(int j=1;j<11;j++){
			if (*Y==i && *X==j)       //Randomly created with rand()
				printf("E\t");
			else if (i==6 && j==6)    //Because of our location is (6,6)
				printf("O\t");
			else
				printf(".\t");        //Other cases
		}
		printf("\n");
	}
	printf("Enemies X Position %d, Y Position %d, Displacement: %.2f, Distance to our camp: %.2f \nCommand Waiting:\n",*Y,*X,*R,*D ); 
	if(*Y ==6 && *X==6)
		printf("Oh!We need to refresh.\n");
}

void track_machine (){
	char EorR='R';
	int enLOC_x=1,enLOC_y=0,oldEnLOC_x=0,oldEnLOC_y=0,check=1;	//Enemy locations
	double d,r;
	/*Printing the field*/
	for(int i=1;i<11;i++){
		for(int j=1;j<11;j++){
			/*Because of 11x11 map is between 1 and 11 && initial position of enemies 0,0 , so E won't be shown in the map	*/
			if (i==6 && j==6)		//Because of our location is (6,6)
				printf("O\t");
			else
				printf(".\t");          //Other cases 
		}
		printf("\n");
	}

	printf("Enemies X Position 0, Y Position 0, Displacement: 0, Distance to our camp: 8.48\nCommand waiting:" ); 

	while(check==1){
		
		scanf(" %c",&EorR);
		if(EorR=='E'){
				check=0;
				break;
		}
		else if(EorR=='R'){
				//Randomly created with rand() between 1 and 11
				srand(time(NULL));			
				enLOC_x=rand()%10+1;         
		    	enLOC_y=rand()%10+1;
		 		/*D is Distance to our position (6,6). R is enemies' displacement with old position.*/
			   	r= sqrt( (enLOC_y*1.0-oldEnLOC_y*1.0)*(enLOC_y*1.0-oldEnLOC_y*1.0) + (enLOC_x*1.0-oldEnLOC_x*1.0)*(enLOC_x*1.0-oldEnLOC_x*1.0) );
		    	d= sqrt( (enLOC_y-6.0)*(enLOC_y-6.0) + (enLOC_x-6.0)*(enLOC_x-6.0) );
		    	refresh_position(&enLOC_x, &enLOC_y, &d, &r);
		    	/*Assigning current position to old position.*/
		    	oldEnLOC_x=enLOC_x;        
		    	oldEnLOC_y=enLOC_y;
		}
		else{
			printf("Invalid character! Try Again: ");
			continue;
		}
	}

}
		/*		PART4		*/
int decrypt_char (char character){
	switch(character){
		case ' ':
			return 0;
		case '-':
			return 1;
		case '_':
			return 2;
		case '|':
			return 3;
		case '/':
			return 4;
		case '\\':
			return 5;
		case 'O':
			return 6;
	}
}

void encrypt_messages(char* file_path){
	int number_i=0,number_i_j=0,buffer,buffer2,buffer3;
	char charbuffer;
	FILE *filep= fopen(file_path,"r");
	FILE *filep2= fopen("encrypted_p4.img","w");
	if(filep==NULL || filep2==NULL){
		printf("COuldn't open file.");
		return;
	}	
	/*buffers will be used for storing characters and numbers in memory*/
	buffer=0,buffer2=0,buffer3=0;  
	while(fscanf(filep, "%c", &charbuffer) == 1){
		fprintf(filep2,"%d",number_i);
		buffer3=buffer2;
		buffer2=buffer;

		if(charbuffer=='\n'){
			fprintf(filep2,"%c",charbuffer);
			buffer=0,buffer2=0,buffer3=0;
			fscanf(filep,"%c",&charbuffer);
			if(charbuffer=='\n'){
				fprintf(filep2,"%c",charbuffer);
				fscanf(filep,"%c",&charbuffer);
				fscanf(filep,"%c",&charbuffer);
			}
		}
		/*converting text to decrypted numbers.*/
		buffer=decrypt_char(charbuffer);

		number_i_j=buffer+buffer2+buffer3;
		number_i=number_i_j % 7;	
	}
	fclose(filep);
	fclose(filep2);
}

void menu (){
	int choice,check=1;

	while(check==1){
		printf("1-)Decrypt and print encrypted_p1.img\n");
		printf("2-)Decrypt and print encrypted_p2.img\n");
		printf("3-)Switch on the tracking machine\n");
		printf("4-)Encrypt the message\n");
		printf("5-)Switch off\n\nPlease make a choice:\n");

		while(scanf("%d",&choice) != 1 && getchar() != '\n')      //Prevent infinite loop if user enters character instead of integer.
			printf("You entered an unsupported character.\n");

		switch(choice){
			case 1:
				decrypt_and_print("encrypted_p1.img");
				break;
			case 2:
				deep_decrypt_and_print("encrypted_p2.img");
				break;
			case 3:
				track_machine();
				break;
			case 4:
				encrypt_messages("decrypted_p4.img");
				break;
			case 5:
				printf("Goodbye\n");
				check=0;
				break;
			default:
				printf("You entered an unsuported character. Enter again:\n");
		}

	}

}

int main(){
	menu();
	return 0;
}