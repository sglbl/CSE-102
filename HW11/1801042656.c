#include <stdio.h>
#include <stdlib.h>	
#include <time.h>
#include <math.h>

typedef struct node {
	int num;
	struct node *nextptr;
}node;

typedef struct difference{
	int n1, n2;
}difference;
		/*	 PART2   */
void show_llist(node *strnode2){
	if(strnode2==NULL){     
		printf("List is empty.");
		return;
	}
	while (strnode2 != NULL){
		printf("%d ",strnode2->num);
		strnode2 = strnode2->nextptr;
	}
	printf("\n");
}

void add_to_llist(node* root, int number){
	node* temp = root;
	root = (node*)malloc(sizeof(node));
	if (root ==NULL){
		printf("Error in add_to_llist function \n");
		return;
	}
	root -> num = number;
	root -> nextptr = NULL;
	while(temp->nextptr != NULL)
    	temp = temp->nextptr;

    temp->nextptr = root;
    root -> nextptr = NULL;
}

difference* difference_Array(int counter, node *strnode2, int *array, int *difcounter){ //Dynamically creating array.
	int howmanydifferent=0;
	difference * difArray = (difference*)malloc(sizeof(difference));

	for(int i=0; i<counter; i++){
		if(array[i] != strnode2->num){
			howmanydifferent++;
			difArray = (difference*)realloc(difArray, howmanydifferent*sizeof(difference));
			difArray[howmanydifferent-1].n1 = array[i];
			difArray[howmanydifferent-1].n2 = strnode2->num;
		}
		if(strnode2 != NULL )   strnode2 = strnode2->nextptr;
	}
	*difcounter = howmanydifferent;

	return difArray;
}

void part2(){
	int number, counter, difcounter, *currentPointer = NULL;// Numbers will be stored in currentPointer[] array.(cp will point to first element's adress.)
	node *head, *strnode2=NULL; 
	difference *difArray;

	counter=0;
    currentPointer= (int*)malloc(sizeof(int));
	printf("\nPART 2 \nInsert numbers to array as much as you want: (Enter 'q' to stop)\n");
	while( scanf("%d", &currentPointer[counter]) == 1 ){
		counter++;
    	if(counter%5==0)
    		currentPointer= (int*)realloc(currentPointer, 5*counter*sizeof(int));
	}
	getchar();	//to destroy garbage char q. 
	printf("Please insert %d numbers to linked list: \n", counter);

	while (scanf("%d ", &number) !=1 && getchar() != '\n') printf("Wrong character. Enter again: ");		
	strnode2 = (node*)malloc(sizeof(node));			//Inserting first element to linked list.
	strnode2 -> num = number;
	head = strnode2;  		//storing adress of strnode2's head.  (It will be used every time strnode2 changed.)
	strnode2 -> nextptr = NULL;

	for(int i=0; i<counter-1; i++){
		while (scanf("%d", &number) !=1 && getchar() != '\n') printf("Wrong character. Enter again: ");		
		add_to_llist(strnode2, number);
	}

	printf("Array  elements are: ");
	for(int i=0; i<counter; i++)  printf("%d ",currentPointer[i] );
	printf("\n");
	strnode2 = head;
	printf("L.List elements are: ");
	show_llist(strnode2);
	strnode2 = head;

	difcounter=0;
	difArray = difference_Array(counter, strnode2, currentPointer, &difcounter);

	printf("There are %d different number(s) in list\n",difcounter );
	for(int i=0; i<difcounter; i++)
		printf("%d and %d\n", difArray[i].n1, difArray[i].n2);
}

	/*		PART1 		*/
float* stats_linkedlist(node* strnode, int *llmemoryusage){
	int max, min, count;
	size_t stdsum;
	float *result;
	node* temp = strnode;			//Every time my job has done with temp, i will initialize it to show head adress(for using it again)
	count=0;
	while(temp -> nextptr != NULL){
		count++;
		temp = temp ->nextptr;
		if(temp -> nextptr == NULL)
			count++;	
	}
	*llmemoryusage = count * sizeof(int)*2; // (sizeof(int) + 4) * counter
	temp=strnode;

	result=(float*)calloc(4,sizeof(node));
	min=temp->num, max=temp->num;
	while(temp -> nextptr != NULL){		//Finding min and max values.
		if( temp->num > max)
			max = temp->num;
		if( temp->num < min)
			min = temp->num;
		temp = temp -> nextptr;
		if(temp -> nextptr == NULL){	//For last num of the l.list
			if( temp->num > max)	max = temp->num;
			if( temp->num < min)	min = temp->num;
		}
	}
	result[0]=min*1.0, result[1]=max*1.0;
	temp=strnode;

	result[2]=0.0;		//This will hold the mean of the linked list.
	while(temp -> nextptr != NULL){		//Finding mean of the array.
		result[2] += temp->num;
		temp = temp -> nextptr;
		if(temp -> nextptr == NULL)	result[2] += temp->num;	//For last num of the l.list
	}
	result[2] /= (count*1.0);
	temp=strnode;

	stdsum=0;
	while(temp -> nextptr != NULL){		//Finding standart deviation of the array.
		stdsum += (temp->num - result[2])*(temp->num - result[2]);
		temp = temp -> nextptr;
		if(temp -> nextptr == NULL)	stdsum += (temp->num - result[2])*(temp->num - result[2]);	//For last num of the l.list
	}
	result[3] = sqrt( stdsum/ (count*1.0) );
	temp=strnode;

	return result;
}

node* read_linkedlist(char *filename){
	int buffer;
	node *head, *strnode=NULL;
	FILE *filep=fopen(filename,"r");
	if (filep == NULL){
        printf("Couldn't open file\n");
        exit(-1);
    }

    fscanf(filep, "%d,", &buffer);
    strnode=(node*)malloc(sizeof(node));
    strnode->num = buffer;
 	strnode->nextptr = NULL;
 	head = strnode;
 
 	while( fscanf(filep, "%d,", &buffer)==1 ){
 		strnode->nextptr=(node*)malloc(sizeof(node));
 		strnode->nextptr->num = buffer;
 		strnode->nextptr->nextptr=NULL;
 		strnode = strnode->nextptr;
 	}
 	strnode=head;
 	fclose(filep);
 	return strnode;
}

float* stats_array(int* array, int *arraymemoryusage){
	int max,min,count=0;
	size_t j,stdsum;
	float *result;
	while(array[count] != '\0')
		count++;
	*arraymemoryusage = count*sizeof(int);		//It will pass by reference.
	result=(float*)calloc(4,sizeof(node));

	max=array[0], min=array[0], result[2]=0.0;
	for(int i=0; i<count; i++){		//Finding min, max and mean of the array.
		result[2] += array[i];		//At the last, result[2] will hold the average of numbers(mean)
		if(array[i]> max)
			max = array[i];
		if(array[i] < min)
			min = array[i];	
	}
	result[2] = result[2]/((count)*1.0);
	result[0]=min, result[1]=max;

	stdsum=0;
	for(j=0; j<count; j++)			//Finding standart deviation of the array.
		stdsum += ((array[j]-result[2] )*(array[j]-result[2] ));
	result[3]=sqrt ((float)( stdsum/ (count) ));

	return result;
}

int* read_array(char *filename){
	FILE *filep;
	int counter, *currentPointer=NULL;
	filep=fopen(filename,"r");
	if (filep == NULL){
        printf("Couldn't open file\n");
        return 0;
    }

	counter=0;
    currentPointer= (int*)calloc(1000, sizeof(int));
    while( fscanf(filep,"%d,",&currentPointer[counter]) == 1 ){
    	counter++;
    	if( counter%1000 == 0 )
    		currentPointer= (int*)realloc(currentPointer, 1000*counter*sizeof(int));
    }
    fclose(filep);
    return currentPointer;
}

void part1(){
	node* llistreading;
	int* arrayreading, arraymemoryusage, llmemoryusage;
	float *resultofarray, *resultofllist;
	double totaltime[4];
	clock_t se;

	se = clock();		//Calculating read_array function's speed.
	arrayreading = read_array("list.txt");
	se = clock() - se;
	totaltime[0] = ((double)se)/CLOCKS_PER_SEC;

	se = clock();		//Calculating stats_array function's speed.
	resultofarray = stats_array(arrayreading, &arraymemoryusage);
	se = clock() - se;
	totaltime[1] = ((double)se)/CLOCKS_PER_SEC;

	se = clock();		//Calculating read_linkedlist function's speed.
	llistreading = read_linkedlist("list.txt");
	se = clock() - se;
	totaltime[2] = ((double)se)/CLOCKS_PER_SEC;

	se = clock();		//Calculating stats_linkedlist function's speed.
	resultofllist = stats_linkedlist(llistreading, &llmemoryusage);
	se = clock() - se;
	totaltime[3] = ((double)se)/CLOCKS_PER_SEC;
	//I will run these process totally 4 times for each in different order //2nd time
	se = clock();	llistreading = read_linkedlist("list.txt");                      se = clock() - se;   totaltime[2] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();   arrayreading = read_array("list.txt");                           se = clock() - se;   totaltime[0] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();	resultofarray = stats_array(arrayreading, &arraymemoryusage);    se = clock() - se;	  totaltime[1] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();   resultofllist = stats_linkedlist(llistreading, &llmemoryusage);  se = clock() - se;   totaltime[3] += ((double)se)/CLOCKS_PER_SEC;
	// 3rd time
	se = clock();   arrayreading = read_array("list.txt");                           se = clock() - se;   totaltime[0] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();	llistreading = read_linkedlist("list.txt");                      se = clock() - se;   totaltime[2] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();   resultofllist = stats_linkedlist(llistreading, &llmemoryusage);  se = clock() - se;   totaltime[3] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();	resultofarray = stats_array(arrayreading, &arraymemoryusage);    se = clock() - se;	  totaltime[1] += ((double)se)/CLOCKS_PER_SEC;
	//4th time
	se = clock();   resultofllist = stats_linkedlist(llistreading, &llmemoryusage);  se = clock() - se;   totaltime[3] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();   arrayreading = read_array("list.txt");                           se = clock() - se;   totaltime[0] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();	resultofarray = stats_array(arrayreading, &arraymemoryusage);    se = clock() - se;	  totaltime[1] += ((double)se)/CLOCKS_PER_SEC;
	se = clock();	llistreading = read_linkedlist("list.txt");                      se = clock() - se;   totaltime[2] += ((double)se)/CLOCKS_PER_SEC;

	printf("READING ARRAY STATICS\n");
	printf("Array's total memory usage is %d bytes\n",arraymemoryusage);
	printf("Min number is: %.0f\n", resultofarray[0] );
	printf("Max number is: %.0f\n", resultofarray[1] );
	printf("Mean is: %.2lf\n", resultofarray[2] );
	printf("Std Deviation is: %.2f\n",  resultofarray[3] );
	printf("Total time passed for read_array (..) function is %lf sec\n", totaltime[0]/4);
	printf("Total time passed for stats_array(..) function is %lf sec\n", totaltime[1]/4);
	free(arrayreading);	free(resultofarray);

	printf("\nREADING LINKED LIST STATICS\n");
	printf("L.List's Total memory usage: %d bytes\n",llmemoryusage);		
	printf("Min number is: %.0f\n", resultofllist[0] );
	printf("Max number is: %.0f\n", resultofllist[1] );
	printf("Mean is: %.2lf\n", resultofllist[2] );
	printf("Std Deviation is: %.2f\n",  resultofllist[3] );	
	printf("Total time passed for read_linkedlist (..) function is %lf sec\n", totaltime[2]/4);
	printf("Total time passed for stats_linkedlist(..) function is %lf sec\n", totaltime[3]/4);	
	free(llistreading);	free(resultofllist);
}

int main(){
	part1();
	part2();
	return 0;
}