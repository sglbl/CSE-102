#include <stdio.h>
#include <math.h>
//Suleyman GOLBOL_1801042656
 void find_root(){
 	int a,b,c,delta;
 	float root1,root2,square_root_of_delta;

 	printf("Please enter the a,b,c numbers up to ax²+bx+c=0\n");
 		printf("Please enter the first coefficient\n");
 		scanf("%d",&a);
 		printf("Please enter the second coefficient\n");
 		scanf("%d",&b);
 		printf("Please enter the third coefficient\n");
 		scanf("%d",&c);

 	delta=b*b-4*a*c;
 	square_root_of_delta=sqrt(delta);
 	root1=(-b + square_root_of_delta) / (2*a) ;
 	root2=(-b - square_root_of_delta) / (2*a) ;

 	if(delta>=0)
 		printf("%dx²+%dx+%d have real roots {%.2f,%.2f}\n",a,b,c,root1,root2);
 	else if(delta<0)
 		printf("Your equation %dx²+ (%d)x+ (%d) does not have any real roots.\n",a,b,c);
 }

 void find_newtonian_root(){

 	int a,b,c,delta,initial,array[3];
 	float root1,root2,xn[10],fx;

 	printf("Please enter the a,b,c numbers up to ax²+bx+c=0\n");
 		printf("Please enter the first coefficient\n");
 		scanf("%d",&a);
 		printf("Please enter the first coefficient\n");
 		scanf("%d",&b);
 		printf("Please enter the first coefficient\n");
 		scanf("%d",&c);
 		printf("Please enter the initial\n");
 		scanf("%d",&initial);
 	printf("Your equation is %dx²+%dx+%d",a,b,c);

 	array[0]=c;
 	array[1]=b;
 	array[2]=a;
 	for(int i=1;i<=2;i++){ //taking differential
		array[i]=i*array[i];
		array[i-1]=array[i];
	}
	printf("\nDerivative of Equation\n");
		for(int i=1;i>=0;i--){
			if(i!=0)
				printf("%d*x^%d + ",array[i],i);
			else
				printf("%d*x^%d \n",array[i],i);
		}
		//Let initial be x0
		xn[0]=initial;
		for(int i=0;i<9;i++){ //applying Newton Method
			xn[i+1]=xn[i]- ( a*xn[i]*xn[i] + b*xn[i]+c)/( 2*a*xn[i]+ b ) ;
			// x(n+1)=x(n) -f(xn)/f'(xn)
		}
		printf("\nAnd iterations are\n");
		printf("Step      x          f(x)      Difference\n"); //The Table
		for(int i=1;i<=5;i++){
			printf("%d        ",i);
			printf("%.4f     ",xn[i]);
			fx=a*xn[i]*xn[i] + b*xn[i]+c;
			printf("%.4f     ",fx);
			printf("%.4f\n",xn[8]-xn[i]);
		}
}

 int find_multiple_closest(int a, int b){
 	int div,onebigger,onesmaller,output;
 	
 	div=(int)(a/b);
 	onebigger=div+1;
 	onesmaller=div; //it is not div-1 because integer div is equal or smaller than a/b.

 	if( ((onebigger-1)*b-a) == (a-onesmaller*b) ){  // if a = k*b 
 		output=a;
 		printf("Closest number to %d that is multiple of %d is %d itself\n",a,b,output);
 	}
 	else if( (onebigger*b-a) > (a-onesmaller*b) ){
 		output=(onesmaller*b);
 		printf("Closest number to %d that is multiple of %d is %d\n",a,b,output);
 	}
 	else if( (onebigger*b-a) < (a-onesmaller*b) || (onebigger*b-a) == (a-onesmaller*b) ){
 		output=(onebigger*b);
 		printf("Closest number to %d that is multiple of %d is %d\n",a,b,output);
 	}

 }

int main(){
	printf("--------PART 1-------\n");
	find_root();
	printf("\n\n--------PART 2-------\n");
	find_newtonian_root();

	int m,n;
	printf("\n--------PART 3-------\nEnter the first integer: ");
	scanf("%d",&m);
	printf("Enter the second integer: ");
	scanf("%d",&n);
	find_multiple_closest(m,n);
	
	return 0;
}