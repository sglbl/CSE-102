#include <stdio.h>
#include <math.h>

int isprime(int a){
	int x,flag=0;
		for(x=2; x<= sqrt(a) ; x++){
			if(a%x==0){  //it means that the number is not a prime number.
				flag=x;
				break;
			}
		}
		return flag;		//It returns the number can divisible by it.
}

int main(){
	int num;
	printf("Please enter an integer: ");
	for(;scanf("%d",&num) != 1 || num<=1 ;){  // Checking if condition is true
		for(;getchar() != '\n';);
    		printf ("ERROR! It is smaller than 1 or not a number. Try again:\n");
	}

	for(int i=2;i<num;i++){
		if(isprime(i) == 0)
			printf("%d is a prime number.\n\n",i);
		else if(isprime(i) != 0)
			printf("%d is not a prime number, it is divisible by %d\n\n",i,isprime(i));
	}

	return 0;
}