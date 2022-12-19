#include <stdio.h>

int myDigitNumFinder(int b){ //This a function that how many digit a number has.
	int length=1;
	while(b/10 != 0){
		b /= 10;
		length++;
	}

	return length;
}

int My10Pow(int exponent){ //This a function that finds 10's exponents.
	int result=1;
	while( exponent != 0 ){
		result *=10;
		exponent--;
	}

	return result;
}

int andop(int a, int b){
	int length1= myDigitNumFinder(a);
	int length2= myDigitNumFinder(b);

	int i=1,result=0;  
	while(i != length1+1){  //length1 and length2 are same.
		if ( (int)(a /My10Pow(length1-i)) % 10 == (int)(b/My10Pow(length1-i)) % 10 ){
			if ( (int)(a /My10Pow(length1-i)) % 10 == 1){
				result *=10;
				result +=1;
			}
			else
				result *=10;
		}

		else if ( (int)(a /My10Pow(length1-i)) % 10 != (int)(b/My10Pow(length1-i)) % 10 )
			result *=10;

		i++;
	}
	return result;
}
	

int main(){
	int num1, num2, length1, length2, digitof1, digitof2, check=1;
	
	while(1){
		check=1;
		printf("First integer:  ");
			while( scanf("%d",&num1) != 1 && getchar() != '\n' ) // to prevent infinite loop.
				printf("You entered a unsupported character. TRY AGAIN:\n");
			
		printf("Second integer: ");
			while( scanf("%d",&num2) != 1 && getchar() != '\n')
				printf("ERROR.You entered a unsupported character. TRY AGAIN:\n");

		length1= myDigitNumFinder(num1);
		length2= myDigitNumFinder(num2);
		
		if(length2 != length1){
			printf("Integers should have the same length, please enter 2 new integers.\n");
			check=0;
		}

		//if program reached here, then it means lengths are equal.
		if(check==1){	
			int i=0;
			while( i != length1+1 ){
				/* checking the digits whether they contain numbers except 1 and 0 */
				digitof1= (int)( num1/My10Pow(i) ) % 10  ; 
				digitof2= (int)( num2/My10Pow(i) ) % 10  ;

				if( digitof1  != 0 && digitof1  != 1){
						printf("Integers should be binary, please enter 2 new integers.\n");
						check=0;
						break;
				}
				if( digitof2 != 0 && digitof2 != 1){
						printf("Integers should be binary, please enter 2 new integers.\n");
						check=0;
						break;
				}
				i++;
			}

			//if program reached here, then it means numbers contain just 0 or 1.
			if(check==1){	
				printf("\n%d AND %d = ",num1,num2);
				printf("%d \n",andop(num1,num2));
				return 0;
			}
		}
	
	}
	return 0;
}