#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

Figure* start_figure(double width, double height){
	Figure* figure;
	figure = (Figure*)malloc(sizeof(Figure));

	// (0,0) points are the center of the canvas.
	figure-> max.x = (double)width/2; //Max and min boundary points in canvas.
	figure-> max.y = (double)height/2;
	figure-> min.x = (double)-width/2;
	figure-> min.y = (double)-height/2;
	return figure;
}

void set_thickness_resolution(Figure* fig, double thickness, double resolution){
	fig->thick = thickness;
	fig->res   = resolution;
}

void set_color(Figure* fig, Color c){
	Color *cl=&c;
	fig->col.red   = cl->red;
	fig->col.green = cl->green;
	fig->col.blue  = cl->blue;
	cl = NULL;
	free(cl);
}

void draw_fx(Figure* fig, double f(double x), double start_x, double end_x, double step_size){
	double i=start_x;
	Point2D* temp;
	
	fig->currentPoint = (Point2D*)malloc(sizeof(Point2D));
	fig->currentPoint->x = i;
	fig->currentPoint->y = f(i);
	fig->nextptr = NULL;
	fig->treevalue = NULL;  // for not to call export_tree() function.
	temp = fig->currentPoint;
	i += step_size;
	Point2D* old = temp;

	while( i < end_x ){
		temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
		temp->nextptr->x = i;
		temp->nextptr->y = f(i);
		temp->nextptr->nextptr = NULL;	// temp->nextptr->nextptr = (Point2D*)malloc(sizeof(Point2D));
		
		temp = temp->nextptr;
		i += step_size;
	}
	
}

void draw_ellipse(Point2D * centre, Point2D * width_height, Figure* fig){
	Point2D* temp;
	double width, height, centerX, centerY, startX;
	double xovera, bsquare;

	fig->treevalue = NULL;	 // for not to call export_tree() function.
	fig->tree      = NULL;
	fig->counter   = 0.0;
	width = width_height->x, height = width_height->y;		//Let be x=width and y=height
	centerX = centre->x, centerY = centre->y;				//Center coordinates

	fig->currentPoint = (Point2D*)malloc(sizeof(Point2D));
	fig->currentPoint->x = width;
	fig->currentPoint->y = height;
	fig->nextptr = NULL;
	temp = fig->currentPoint;
	
	startX = -fig->currentPoint->x; 
	while(startX < fig->currentPoint->x ){						// Upside of the ellipse
		temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
		temp->nextptr->nextptr = NULL;
		temp->nextptr->x = startX + centerX;
		xovera  = pow(startX/fig->currentPoint->x,2);
		bsquare = pow(fig->currentPoint->y,2);
		temp->nextptr->y = sqrt((1-xovera)*bsquare) + centerY;
		startX = startX + 1/fig->res;
		temp = temp->nextptr;
	}

	startX = fig->currentPoint->x;  
	while( -fig->currentPoint->x < startX){						// Downside of the ellipse
		temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
		temp->nextptr->nextptr = NULL;
		temp->nextptr->x = startX + centerX;
		xovera  = pow(startX/fig->currentPoint->x,2);
		bsquare = pow(fig->currentPoint->y,2);
		temp->nextptr->y = -sqrt((1-xovera)*bsquare) + centerY;
		startX = startX - 1/fig->res;
		temp = temp->nextptr;
	}

	temp->nextptr = (Point2D*)malloc(sizeof(Point2D));			// Rest part of the ellipse
	temp->nextptr->nextptr = NULL;
	temp->nextptr->x = -fig->currentPoint->x + centerX;
	temp->nextptr->y = centerY;

	fig->currentPoint = fig->currentPoint->nextptr;				// Deleting the line in the middle
}

void draw_polyline(Point2D* poly_line, int n, Figure* fig){
	Point2D *temp=NULL , *temp2 = NULL;
	fig->currentPoint = (Point2D*)calloc(n, sizeof(Point2D));
	fig->nextptr   = NULL;
	fig->treevalue = NULL;	 // for not to call export_tree() function.
	fig->tree      = NULL;
	fig->counter   = 0.0;
	temp = (Point2D*)malloc(sizeof(Point2D));
	temp = fig->currentPoint;
	temp2 = temp;

	for(int i=0; i<n; i++){
		temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
		temp->nextptr->x = poly_line[i].x;
		temp->nextptr->y = poly_line[i].y; 
		temp = temp->nextptr;
	}
	temp->nextptr = NULL;
}

void draw_polygon(Point2D * poly_line, Figure *fig){
	int counter,size;
	Point2D *temp, *temp2;

	fig->treevalue = NULL;	 // for not to call export_tree() function.
	fig->tree      = NULL;
	fig->counter   = 0.0;
	size =  poly_line->size;  // size is equal to n value in poly_line function.
	fig->currentPoint = (Point2D*)calloc(size+1, sizeof(Point2D));
	fig->nextptr = NULL;
	temp = fig->currentPoint;
	temp2 = temp;

	counter = 0;
	while(counter != size){
		temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
		temp->nextptr->nextptr = NULL;
		temp->nextptr->x = poly_line[counter].x;
		temp->nextptr->y = poly_line[counter].y;
		temp = temp->nextptr;
		counter++;
	}
	temp->nextptr = (Point2D*)malloc(sizeof(Point2D));
	temp->nextptr->nextptr = NULL;
	temp->nextptr->x = poly_line[0].x;
	temp->nextptr->y = poly_line[0].y;
	temp->nextptr->nextptr = NULL;

	fig->currentPoint = fig->currentPoint->nextptr;
	fig->nextptr = NULL;
}

void add_to_eps(Tree *tree, int *counter, int *array){
	if(tree){
		array[*counter] = tree->data;
		(*counter)++; 
		add_to_eps(tree->left,  counter, array);
		add_to_eps(tree->right, counter, array);
	}
}

int is_even(int num){
	return num%2 + 1;
}

void draw_binary_tree(Tree *root, Figure* fig){
	TreeValues *temp;
	int iarray[30], counter;
	Point2D pointTemp, pointTemp2, array[30];
	int arraycounter;
	double difx,dify;

	fig->tree = (Tree*)malloc(sizeof(Tree));
	fig->tree->left  = NULL;
	fig->tree->right = NULL;
	fig->tree = root;

	counter = 0;
	add_to_eps(fig->tree, &counter, iarray); // counter and array changed.
	fig->counter = counter;
	fig->treevalue = (TreeValues*)malloc(sizeof(TreeValues));
	fig->treevalue->data = iarray[0];
	fig->treevalue->nextptr = NULL;
	temp = fig->treevalue;

	for(int i=1; i<counter; i++){
		temp->nextptr = (TreeValues*)malloc(sizeof(TreeValues));
		temp->nextptr->data = iarray[i];
		temp->nextptr->nextptr = NULL;
		temp = temp->nextptr;
	}

	temp= fig->treevalue;
	// Now every value sent to TreeValues.
	temp = NULL;

	counter = fig->counter;
	temp = fig->treevalue;
	temp->point.x = (fig->max.x-fig->min.x)/10.0;
	temp->point.y = (fig->max.y-fig->min.y)/2.7; 
	array[0].x = temp->point.x, array[0].y = temp->point.y;
	difx = fig->max.x/3.3;
	dify = fig->max.y/3.3;

	fig->difx = difx;
	fig->dify = dify;

	arraycounter=1;
	pointTemp2 = temp->point;
	for(int i=0; i<counter-1; i++){
		pointTemp = temp->point;
		temp->nextptr->point.x = temp->point.x - difx;
		array[arraycounter].x = temp->point.x-difx, array[arraycounter].y = temp->point.y-dify;
		arraycounter++;
		counter--;
		if(i==counter-1)	break;
		array[arraycounter].x = temp->point.x+difx, array[arraycounter].y = temp->point.y-dify;
		arraycounter++;

		if     (is_even(i)==1)	temp->nextptr->point.x = temp->point.x-difx;
		else if(is_even(i)==2)	temp->nextptr->point.x = temp->point.x+difx;
		temp->nextptr->point.y = temp->point.y-dify;
		temp = temp->nextptr;
	}

	for(int i=0; i<fig->counter; i++)	fig->treear[i] = array[i];
	fig->nextptr = NULL;
}

void export_tree(Figure * fig, char * file_name){
	FILE *filep = fopen(file_name,"w");
	TreeValues *temp = NULL;
	Point2D pointTemp, pointTemp2, array[30];
	int counter, arraycounter;
	double difx,dify;
	fprintf(filep, "%%!PS-Adobe-3.0 EPSF-3.0 \n");
	fprintf(filep, "%%%%BoundingBox: %.3f %.3f %.3f %.3f\n",fig->min.x, fig->min.y, fig-> max.x, fig-> max.y);
	fprintf(filep, "%.2f setlinewidth\n%.2f %.2f %.2f setrgbcolor\n", fig->thick, fig->col.red, fig->col.green, fig->col.blue);

	difx = fig->difx;
	dify = fig->dify;
	counter = fig->counter;
	for(int i=0; i<counter; i++)	
		array[i] = fig->treear[i];
	arraycounter=1;
	temp = fig->treevalue;
	pointTemp2 = temp->point;
	for(int i=0; i<counter-1; i++){
		fprintf(filep, "%lf %lf moveto\n",array[arraycounter].x+difx, array[arraycounter].y+dify);
		fprintf(filep, "%lf %lf lineto\n",array[arraycounter].x, array[arraycounter].y); //left  leaf
		arraycounter++;
		counter--;
		if(i==counter-1)	break;
		fprintf(filep, "%lf %lf moveto\n",array[arraycounter].x-difx, array[arraycounter].y+dify);
		fprintf(filep, "%lf %lf lineto\n",array[arraycounter].x, array[arraycounter].y); //right leaf
		arraycounter++;
	}

	fprintf(filep, "stroke\n");
	fprintf(filep, "/monospace findfont\n22 scalefont\nsetfont\n");

	temp = fig->treevalue;
	counter = fig->counter;
	for(int i=0; i<counter; i++){
		//Firstly drawing circle with arc.
		fprintf(filep, "%lf %lf 40 0 360 arc closepath gsave 2 setgray fill grestore stroke\n", array[i].x, array[i].y);
		fprintf(filep, "%lf %lf moveto (%d) show stroke\n", array[i].x-10, array[i].y-10, temp->data  );	//centre of circle
		temp = temp->nextptr;
	}
	fig->nextptr = NULL;
}

void scale_figure(double scale_x, double scale_y, Figure* fig){
	Point2D* temp= NULL, *temp2 = NULL;
	Figure figTemp;
	TreeValues *ttemp = (TreeValues*)malloc(sizeof(TreeValues));
	if(fig->currentPoint == NULL){  // For binary trees.
		ttemp->nextptr = (TreeValues*)malloc(sizeof(TreeValues));
		ttemp->point = fig->treevalue->point;
		for(; ttemp->nextptr != NULL; ttemp = ttemp->nextptr){
			ttemp->point.x *= scale_x;
			ttemp->point.y *= scale_y;
		}
		return;
	}
	
	//If program reaches here then it means it's not a binary tree.
	temp = fig->currentPoint;
	temp2 = fig->currentPoint;
	figTemp.max.x = fig->currentPoint->x;
	figTemp.min.x = fig->currentPoint->x;
	figTemp.max.y = fig->currentPoint->y;
	figTemp.min.y = fig->currentPoint->y;

	temp2 = temp;
	temp = temp->nextptr;
	for(; temp != NULL; temp = temp->nextptr){
		if     ( figTemp.max.x < temp->x ) figTemp.max.x = temp->x;
		else if( figTemp.min.x > temp->x ) figTemp.min.x = temp->x;
	}

	temp = temp2;
	temp = temp->nextptr;
	for(; temp != NULL; temp = temp->nextptr){
		if     ( figTemp.max.y < temp->y ) figTemp.max.y = temp->y;
		else if( figTemp.min.y > temp->y ) figTemp.min.y = temp->y;
	}

	figTemp.max.x = figTemp.max.x + figTemp.min.x;
	figTemp.max.x = (double)figTemp.max.x/2;
	figTemp.max.y = figTemp.max.y + figTemp.min.y;
	figTemp.max.y = (double)figTemp.max.y/2;
	//I will use these points as center of it.

	temp = temp2;    //temp is my cursor
	for(; temp != NULL; temp = temp->nextptr){
		temp->x = temp->x*scale_x - figTemp.max.x*(scale_x-1);
		temp->y = temp->y*scale_y - figTemp.max.y*(scale_y-1);
		if(temp->nextptr == NULL)	break;
	}
	
	temp = NULL;
}

void resize_figure(Point2D *start_roi, Point2D *end_roi, Figure* fig){//
	fig->min.x = start_roi->x	,	fig->min.y = start_roi->y;
	fig->max.x = end_roi->x  	,	fig->max.y = end_roi->y;
}

void append_figures(Figure * fig1, Figure * fig2){
	Figure *temp = NULL;
	temp = fig1;
	// Rearranging the size of the canvas.
	if(fig1->max.x * fig1->max.y < fig2->max.x * fig2->max.y){
		fig1->max.x = fig2->max.x;
		fig1->max.y = fig2->max.y;
		fig1->min.x = fig2->min.x;
		fig1->min.y = fig2->min.y;
	}

	for(; temp->nextptr != NULL; temp = temp->nextptr);
	temp->nextptr = fig2;
}

void export_eps(Figure * fig, char * file_name){
	Point2D* temp  = NULL;
	Point2D* temp2 = NULL;
	Figure *figTemp;
	FILE* filep = fopen(file_name,"wt");
	if(filep == NULL){
		printf("Couldn't open file.\n");
		return;
	}

	fprintf(filep, "%%!PS-Adobe-3.0 EPSF-3.0 \n");
	fprintf(filep, "%%%%BoundingBox: %.3f %.3f %.3f %.3f\n",fig->min.x, fig->min.y, fig-> max.x, fig-> max.y); //

	while(fig != NULL){
		if(fig->counter != 0.0 && fig->tree != NULL){
			export_tree(fig, file_name);
			//f(fig->nextptr != NULL)	fig = fig->nextptr;
			return;
		}
		
		else 						break;
	}
	// If program reaches here; it means fig is not a tree.
	figTemp = fig;
	if(figTemp != NULL && figTemp->currentPoint != NULL){
		temp = figTemp -> currentPoint;	
		if(temp->nextptr != NULL){
			temp = temp->nextptr;
			temp2 = temp;
		}
		if(temp==NULL){     
			printf("Fig is empty.");
			return;
		}
	}

	for(; figTemp != NULL; figTemp = figTemp->nextptr){
		temp = figTemp -> currentPoint;
		fprintf(filep, "%.2f setlinewidth\n%.2f %.2f %.2f setrgbcolor\n", figTemp->thick, figTemp->col.red, figTemp->col.green, figTemp->col.blue);
		fprintf(filep, "%.5f %.5f moveto\n", temp->x, temp->y );
		while(temp != NULL){
			fprintf(filep,"%lf %lf lineto\n", temp->x, temp->y);
			temp = temp->nextptr; 
		}
		fprintf(filep,"stroke\n");
	}
	fclose(filep);
}