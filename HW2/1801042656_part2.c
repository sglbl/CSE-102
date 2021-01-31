#include <stdio.h>
#include <math.h>

int number_length(int number){
	if(number == 0)
		return 1;
	else
    	return ( log10(number)+1 );
}

int find_digit(int number, int index){
	int length = number_length(number);
	int remaining = index % number_length(number);  //remaining number from division of index over length
												
	int length_digit_6=number %10;							//sixth digit
	int length_digit_5=(int)(number/pow(10,length-5)) %10;  //fifth digit
	int length_digit_4=(int)(number/pow(10,length-4)) %10;  //fourth digit
	int length_digit_3=(int)(number/pow(10,length-3)) %10;  //third digit
	int length_digit_2=(int)(number/pow(10,length-2)) %10;	//second digit
	int length_digit_1=(int)(number/pow(10,length-1)) %10;  //first digit

	if(remaining==0)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_6);
	else if(remaining==1)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_1);
	else if(remaining==2)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_2);
	else if(remaining==3)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_3);
	else if(remaining==4)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_4);
	else if(remaining==5)
		printf("%d. digit of the big number sequence is %d\n",index,length_digit_5);
}

int main(){
	int num,myindex,length;
	printf("Enter a number (maximum of 6 digits number): \n");
	scanf("%d",&num);

	length=number_length(num);
	printf("Length of number is: %d \n",length);

	if(length>6){
		printf("ERROR! Please enter a number that has maximum of 6 digits\n----\n");
		return main();
	}

	printf("When your number is written 100 times next to each other,\nwhich digit of this number would you like to see?\n");
	scanf("%d",&myindex);

	if(myindex > length*100){
		printf("ERROR! You cannot enter a digit bigger than digit of this number.\n----\n");
		return main();
	}
	else
		find_digit(num,myindex);

	return 0;
}