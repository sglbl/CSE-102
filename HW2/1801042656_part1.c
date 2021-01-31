#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int draw_triangle(int side1,int side2, int side3){
	int flag=0;

	if( (side1+side2)<=side3 || (side1+side3)<=side2 || (side2+side3)<=side1 )
		flag=1;
	else if( side1 <= abs(side2-side3) || side2 <= abs(side1-side3) || side3 <= abs(side2-side1) )
		flag=1;

	if(flag==1){
		printf("According to the triangle inequality theorem, this triangle cannot be drawn.\n");
		return 0;
	}
	else if(flag==0){
		printf("According to the triangle inequality theorem, this triangle can be drawn.\n");
		return 1;
	}
}

void type_triangle(int side1,int side2, int side3){
	if(side1==side2==side3)
		printf("The type of the triangle is Equilateral\n");
	else if(side1==side2 || side1==side3 || side2==side3)
		printf("The type of the triangle is  Isosceles\n");
	else
		printf("The type of the triangle is Scalene\n");
}

int perimeter_triangle(int side1,int side2, int side3){
	int perimeter = side1+side2+side3;
	printf("The perimeter of the triangle is: %d\n",perimeter);
	return perimeter;
}

double area_triangle(int side1,int side2, int side3,int perimeter){
	double u=(side1+side2+side3)/2.0;
	double area = sqrt( u*(u-side1)*(u-side2)*(u-side3) );
	printf("The area of triangle is %lf",area);
	return area;
}

int main(){
	int a,b,c;
	printf("The length of the first side:\n");
	scanf("%d",&a);
	printf("The length of the second side:\n");
	scanf("%d",&b);
	printf("The length of the third side:\n");
	scanf("%d",&c);

	int drawing=draw_triangle(a,b,c);

	if(drawing==0)
		return 0;

	type_triangle(a,b,c);
	int perimeter = perimeter_triangle(a,b,c);
	area_triangle(a,b,c,perimeter);
	

	return 0;
}