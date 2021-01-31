#include <stdio.h>

int main(){
	int number,number2,number3;
	double amount;

	printf("***** Welcome to ABC Exchange Office *****\n");
	printf("Enter your amount\n");
	scanf("%lf",&amount);
	printf("Please select your currency\n");
	printf("1. Turkish Lira\n2. Euro\n3. Dollar\n");
	scanf("%d",&number);

	switch (number){
			case 1:
				printf("You have %lf Turkish Liras\n",amount);
				printf("Choose which currency you want to convert\n");
				scanf("%d",&number2);

				switch (number2){
					case 1:
						printf("You have %lf Turkish Liras\n",amount);
						break;
					case 2:
						printf("You have %lf Euros\n",amount/6.69);
						break;	
					case 3:
						printf("You have %lf Dollars\n",amount/6.14);
						break;
					default:
						printf("Your selection is invalid\n");
						break;	
				}
				break;

			case 2:
				printf("You have %lf Euros\n",amount);
				printf("Choose which currency you want to convert\n");
				scanf("%d",&number2);	

				switch (number2){
					case 1:
						printf("You have %lf Turkish Liras\n",amount*6.69);
						break;
					case 2:
						printf("You have %lf Euros\n",amount);
						break;	
					case 3:
						printf("You have %lf Dollars\n",(amount/6.14)*6.69);
						break;
					default:
						printf("Your selection is invalid\n");
						break;	
				}
				break;

			case 3:
				printf("You have %lf Dollars\n",amount);
				printf("Choose which currency you want to convert\n");
				scanf("%d",&number2);

				switch (number2){
					case 1:
						printf("You have %lf Turkish Liras\n",amount*6.14);
						break;
					case 2:
						printf("You have %lf Euros\n",(amount/6.69)*6.14);
						break;	
					case 3:
						printf("You have %lf Dollars\n",amount);
						break;
					default:
						printf("Your selection is invalid\n");
						break;	
				}
				break;

			default:
				printf("Your selection is invalid\n");
				break;	

	}

	printf("If you want to use it again enter 0, to quit enter -1 \n");
	scanf("%d",&number3);

	if(number3==0)
		return main();
	else if(number3==-1)
		return 0;
	else
		return 0;

}