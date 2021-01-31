#include <stdio.h>
#include <math.h>
#define SIZE 500
#define    N 8
void generate_hofstadters_sequence(int *arr, int n){
	/*	Q(n) = Q(n-Q(n-1)) + Q(n-Q(n-2))   && Q(1)=Q(2)=1   */
	int i=2;
	if(n==1)
		return;
	
	arr[i]= arr[i- arr[i-1]] + arr[i- arr[i-2]];
	generate_hofstadters_sequence(arr+1,n-1);
}

int find_max(int arr[], int index, int max_value){
	if(arr[index+1] != 0 ){
		max_value=arr[index];
		return find_max(arr+1,index,max_value);
	}
	else
		return *arr;
}

int sum_array(int arr[]){
	int i=0;
	if(arr[i+1] != 0 )
		return *arr + sum_array(arr+1);
	else
		return *arr;
}

double std_array (int arr[], double *mean, int n, int index){
	double sum;
	if(index>-1){
		*mean += (arr[index]/1.0) / (n/1.0);
		std_array(arr,mean,n,index-1);
		if (index==n-1){
			sum =std_array(arr,mean,n,-1);
			printf("\nSum of these squares are %lf\n",sum );
			return sqrt(sum/(n-1));
		}
	}

	sum =  pow(arr[n-1]-*mean,2);	

	if(n == 1)
		return sum;
	else{
		sum += std_array(arr,mean,n-1,-1) ;
		return sum;
	}
	
	
}

void menuofPart1(){
	int choice,n,index,max,check;
	int arr[SIZE] = {0};
	double mean,std;

	check=1;
	while(check==1){
		printf("Please make your choice:\n-------------\n");
		printf("1) Fill Array\n2) Find Biggest Number \n");
		printf("3) Calculate Sum\n4) Calculate Standart Deviation\n5) Exit\n");
		while( scanf("%d",&choice)!=1 && getchar() !='\n')	printf("Try again!\n"); //To prevent infinite loop
		switch(choice){
			case 1:
				for(int i=0;i< SIZE ;i++)	arr[i]=0;  mean=0; //Filling every
				arr[1]=arr[0]=1;
				printf("Enter a number:\n");
				while( scanf("%d",&n)!=1 && getchar() !='\n')	printf("Try again!\n"); //To prevent infinite loop
				while(n>SIZE-1){
					printf("You entered an unsupported number\n");
					while( scanf("%d",&n)!=1 && getchar() !='\n')	printf("Try again!\n");
				}
				generate_hofstadters_sequence (arr, n-1);
				for (int i=0;i<n;i++) printf("%d  ",arr[i]);
				printf("\n");
				break;
			case 2:
				index=0;
				arr[0]=arr[1]=1;
				if(arr[2]==0){ //That means array is not filled. 
					printf("Array is empty.\n");
					break;
				}
				printf("\nThe max number is %d \n",find_max(arr,index,max) );
				break;
			case 3:
				arr[1]=arr[0]=1;
				if(arr[2]==0){ //That means array is not filled yet.
					printf("Array is empty.\n");
					break;
				}
				printf("\n Sum is: %d\n",sum_array(arr) );	
				break;
			case 4:
				arr[0]=arr[1]=1;
				if(arr[2]==0){ //That means array is not filled yet.
					printf("Array is empty.\n");
					break;
				}
				for(int i=0;i<n;i++)	printf("%d  ",arr[i]);
				index=n-1;
				std=std_array(arr,&mean,n,index);
				printf("Standart deviation is %lf\nMean is: %lf\n",std,mean );
				break;
			case 5:
				check=0;
				break;
			default:
				printf("Error. It is invalid!\n");	
		}

	}

}

	/*   PART2   */
int is_valid_move(int x, int y,int or){
	if     ( or==1 && x>=-2 && y>=-1 && x<N-2 && y<N-1)	return 1;
	else if( or==2 && x>=-1 && y>=2 && x<N-1 && y<N+2 )	return 1;
	else if( or==3 && x>=2 && y>=1 && x<N+2 && y<N+1  )	return 1;
	else if( or==4 && x>=1 && y>=-2 && x<N+1 && y<N-2 )	return 1;
	else if( or==5 && x>=-1 && y>=-2 && x<N-1 && y<N-2)	return 1;
	else if( or==6 && x>=-2 && y>=1 && x<N-2 && y<N+1 )	return 1;
	else if( or==7 && x>=1 && y>=2 && x<N+1 && y<N+2  )	return 1;
	else if( or==8 && x>=2 && y>=-1 && x<N+2 && y<N-1 )	return 1;
	else   return 0;
}
void install_pipes(int visited[N][N],int count, int x, int y, int orientation){
	//	 If visited[x][y] == 1, then it means it's visited ;  if visited[x][y]==0, then it means it's not visited yet.	

	if (count>63)
	{
		visited[x][y] = count;
		int movX[8]={-2,-1,2,1,-1,-2,1,2};
		int movY[8]={-1,2,1,-2,-2,1,2,-1};
		int tempX=0,tempY=0;
		printf("A Proper List:{ ");
		for (int i = 2; i <=64; ++i)
		{
			for (int k = 0; k < 8; ++k)
			{

				if (visited[tempX+movX[k]][tempY+movY[k]]==i)
				{
					tempX=tempX+movX[k];
					tempY=tempY+movY[k];
					printf("O%d,",k+1);
				}
			}
			
		}
		printf(" }\n\n\n");
		visited[x][y] = 0;
	}else{
			if(visited[x+2][y+1] == 0 && is_valid_move(x,y,1) ){        // Orientation1	
				//printf("O1, ");   
				visited[x][y] = count; 
				install_pipes(visited ,count+1, x+2, y+1, 1);
				
			}
			if(visited[x+1][y-2] == 0 && is_valid_move(x,y,2)){   // Orientation2
				//printf("O2, ");   
				visited[x][y] = count; 
				install_pipes(visited, count+1, x+1, y-2, 2);
				
			}
			if(visited[x-2][y-1] == 0 && is_valid_move(x,y,3)){   // Orientation3
				//printf("O3, ");
				visited[x][y] = count; 
				install_pipes(visited, count+1, x-2, y-1, 3);
				
			}
			if(visited[x-1][y+2] == 0 && is_valid_move(x,y,4)){   // Orientation4
				//printf("O4, ");
				visited[x][y] = count; 
				install_pipes(visited, count+1, x-1, y+2, 4);
					
			}
			if(visited[x+1][y+2] == 0 && is_valid_move(x,y,5)){   // Orientation5
				//printf("O5, ");
				visited[x][y] = count;
				install_pipes(visited, count+1, x+1, y+2, 5);
						
			}
			if(visited[x+2][y-1] == 0 && is_valid_move(x,y,6)){   // Orientation6
				//printf("O6, ");
				visited[x][y] = count; 
				install_pipes(visited, count+1, x+2, y-1, 6);
					
			}
			if(visited[x-1][y-2] == 0 && is_valid_move(x,y,7)){   // Orientation7
				//printf("O7, ");
				visited[x][y] = count;
				install_pipes(visited, count+1, x-1, y-2, 7);
					
			}
			if(visited[x-2][y+1] == 0 && is_valid_move(x,y,8)){   // Orientation8
				//printf("O8, ");
				visited[x][y] = count;
				install_pipes(visited, count+1, x-2, y+1, 8);

					
			}
			visited[x][y] =0;
	}

		
}
	/*  PART3  */
char* remove_duplicates (char* str){
	int i=0;
	if(str[i]==0)
		return str;
	else{
		if(str[i]==str[i+1]){
			str[i+1]=str[i+2];
			remove_duplicates(str+1);
		}
		remove_duplicates(str+1);
	}
}

void menu(){
	int cho,visitedplace[N][N],count,check;
	char string[SIZE];

	printf("Welcome to Homework 8, please choose one of the parts to continue:\n");

	check=1;
	while(check==1){
		printf("----------------------\n");
		printf("1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n");
		while( scanf("%d",&cho)!=1 && getchar() !='\n')	   printf("Try again!\n"); //To prevent infinite loop
		switch(cho){
			case 1:
				menuofPart1();
				break;
			case 2:
				count=1;
				for(int i=0;i<N;i++)
					for(int j=0;j<N;j++)
						visitedplace[i][j]=0;	//firstly it is filled with 0 number.

				install_pipes(visitedplace, count, 0, 0, 1);  // it will begin with (0,0) place and orientation1
				break;
			case 3:
				printf("Enter a string: \n");
				getchar();
				fgets(string,SIZE,stdin);
				remove_duplicates(string);
				printf("%s",string);
				break;
			case 4:
				printf("Program is terminating..\n");
				check=0;
				return;
			default:
				printf("You entered something wrong.\n");
		}
	}

}

int main(){
	menu();
	return 0;
}