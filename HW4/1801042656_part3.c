#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
	int enLOC_x=1,enLOC_y=0,oldEnLOC_x=0,oldEnLOC_y=0,check=1;
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


int main(){

	track_machine();
	

	return 0;
}