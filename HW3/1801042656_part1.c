#include <stdio.h>

int sum(int n, int flag){
	int total=0;
	if(flag==0){  //Sum of even numbers
		for(int i=2;i<=n;i+=2){
			if(n-i==1 || n-i==0)
				printf("%d ",i);
			else
				printf("%d + ",i);
			total +=i;
		}
		printf("\n");
	}
	else if(flag==1){ //Sum of odd numbers
		for(int i=1;i<=n;i+=2){
			if(n-i==1 || n-i==0)
				printf("%d ",i);
			else
				printf("%d + ",i);
			total +=i;
		}
	}

	return total;
}

int mult(int n, int flag){
	int product=1;
	if(flag==0){  //Multiplication of even numbers
		for(int i=2;i<=n;i+=2){
			if(n-i==1 || n-i==0)
				printf("%d ",i);
			else
				printf("%d * ",i);
			product *=i;
		}
	}
	else if(flag==1){ //Multiplication of odd numbers
		for(int i=1;i<=n;i+=2){
			if(n-i==1 || n-i==0)
				printf("%d ",i);
			else
				printf("%d * ",i);
			product *=i;
		}
	}

	return product;
}

int main(){
	int num,choice1,choice2,flag;
	printf("Enter an integer:\n");
	scanf("%d",&num);
	printf("Please enter '0' for sum, '1' for multiplication\n");
	scanf("%d",&choice1);

	switch(choice1){
		case 0: 
				printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
				scanf("%d",&choice2);
				switch(choice2){
					case 0:
						flag=0; //For even numbers
						printf("= %d",sum(num,flag));
						break;
					case 1:
						flag=1; //For odd numbers
						printf("= %d",sum(num,flag));
						break;
					default: 
						printf("Invalid value for even/odd selection\n");
				}
			break;

		case 1: 
				printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
				scanf("%d",&choice2);

				switch(choice2){
					case 0:
						flag=0; //For even numbers
						printf("= %d",mult(num,flag));
						break;
					case 1:
						flag=1; //For odd numbers
						printf("= %d",mult(num,flag));
						break;
					default: 
						printf("Invalid value for even/odd selection\n");
				}
			break;
		default: 
			printf("Unsupported operation\n");

	}
	printf("\n");
	return 0;
}