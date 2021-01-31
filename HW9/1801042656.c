#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Hospital{
 char* name;
 char citiesServed[3];
}strHospital;

struct card {
	const char *face;
	const char *suit;
};
typedef struct card scard;
	/*   PART1    */
int numPathsHome(int street, int avenue){
	if(street == 1 || avenue == 1)	
		return 1;
	else
		return numPathsHome(street,avenue-1) + numPathsHome(street-1,avenue);
}

	/*   PART2   */
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]){
	int counter=1;
	strHospital BufferHosresults[4]={
										{ "1", {'A','B','C'} },
										{ "2", {'A','C','D'} },
										{ "3", {'B','F'}     },
										{ "4", {'C','E','F'} }  
									};

	if(_numHospitals<3 && _cities[1]==0)
		  return 0;

	if(_numHospitals > 0){
		char _cities[6]= { 'A', 'B', 'C', 'D', 'E', 'F' };
		results[_numHospitals-1].name = BufferHosresults[_numHospitals-1].name;
		for(int i=0;i<4; i++)
			results[_numHospitals-1].citiesServed[i] = BufferHosresults[_numHospitals-1].citiesServed[i];
		
		canOfferCovidCoverage(_cities, _locations, _numHospitals-1, results);
		printf("Hospital - %s \nHospital locations: %s \n", results[_numHospitals-1].name, results[_numHospitals-1].citiesServed);
	}

	return 1;
}
	/*	PART3	*/
void cards(){
	int a,b,c,d,count=0;
	char check_string[4][13]={0};
	scard var[] =
	{
		{"Hearts",  "Ace"},
		{"Diamonds","Deuce"},
		{"Clubs",   "Three"},
		{"Spades",  "Four"},
		{0, "Five"},
		{0, "Six"},
		{0, "Seven"},
		{0, "Eight"},
		{0, "Nine"},
		{0, "Ten"},
		{0, "Jack"},
		{0, "Queen"},
		{0, "King"}
    } ;
	srand(time(NULL));
	while(count<52){
		a=rand()%4;
		b=rand()%13;
		c=rand()%4;
		d=rand()%13;

		if(check_string[c][d]==0 && check_string[a][b]==0){
			check_string[c][d]=1;
			check_string[a][b]=1;
			printf("%s of %-10s\t",var[a].face,var[b].suit);
			printf("%s of %s \n",var[c].face,var[d].suit);
			count+=2;
		}
		else
			continue;
	}

}

void menu(){
	int choice,check; 		//Menu  variables.
	int street,avenue;		//Part1 variables.
	int choice2;			//Part2 variables.
	strHospital hosresults[4];
	char cities[6]= { 0 };  // Initializing 0 at the beginning to understand if choice is enough for hospital.
	char locations[4][3] = { {'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F'}, {'C', 'E', 'F'} };

	check=1;
	while(check==1){
		printf("Please make your choice:\n-------------\n");
		printf("1) PART1 \n2) PART2 \n");
		printf("3) PART3 \n4) Exit  \n");
		while( scanf("%d",&choice)!=1 && getchar() !='\n')	printf("Try again!\n"); //To prevent infinite loop
		switch(choice){
			case 1:
				printf("Enter the street number?\n");
				while (scanf("%d",&street)!=1 && getchar()!='\n')  printf("Try again:\n");
				printf("Enter the avenue number\n");
				while (scanf("%d",&avenue)!=1 && getchar()!='\n')  printf("Try again:\n");
				printf("\nAnswer is %d\n",numPathsHome(street,avenue));
				break;

			case 2:
				printf("Enter the maximum number of hospitals that can be constructed: ");
				while(scanf("%d",&choice2)!=1 && getchar()!='\n')	printf("Try again: ");
				if(choice2 >4 ){
					printf("There aren't that much hospitals. Enter a number again:\n");	
					while(scanf("%d",&choice2)!=1 && getchar()!='\n')	printf("Try again: ");
				}

				if( canOfferCovidCoverage(cities,locations,choice2,hosresults) == 0)
					printf("No, some cities are not covered.\n");
				else
					printf("Yes, can offer healt care to all!\n");
				break;

			case 3:
				cards();
				break;

			case 4:
				check=0;
				break;
		
			default:
				printf("Error. It is invalid!\n");	
		}
	}

}

int main(){
	menu();
	return 0;
}