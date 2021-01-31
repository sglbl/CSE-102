#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"

void insert(int val, Tree **tree){
	Tree *temp;
	temp = NULL;
    if(*tree == NULL){
        temp = (Tree*)malloc(sizeof(Tree));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }
    if(val < (*tree)->data)
        insert(val, &(*tree)->left);
    else if(val > (*tree)->data)
        insert(val, &(*tree)->right);
}

void free_tree(Tree *rootp){
	Tree *temp2, *temp=rootp;
	for(;temp != NULL; temp=temp->left){
		temp2=temp;
		free(temp2);
	}
	temp=rootp;
	for(;temp != NULL; temp=temp->right){
		temp2=temp;
		free(temp2);
	}
}

void free_tree_value(TreeValues *rootp){
	TreeValues *temp2, *temp=rootp;
	for(;temp != NULL; temp=temp->nextptr){
		temp2=temp;
		free(temp2);
	}
}

void free_point(Point2D *rootp){
	Point2D *temp2, *temp=rootp;
	for(;temp != NULL; temp=temp->nextptr){
		temp2=temp;
		free(temp2);
	}
}

void free_fig(Figure* rootp){
	Figure *temp2, *temp = rootp;
	for(;temp->nextptr != NULL;temp = temp->nextptr){
		temp2 = temp;
		if(temp2->tree != NULL)	     	free_tree (temp2->tree);
		if(temp2->treevalue != NULL)	free_tree_value (temp2->treevalue);
		if(temp2->currentPoint != NULL) free_point(temp2->currentPoint);
		if(temp2 != NULL)		 		free(temp2);
	}
}

int main(){
	Figure *fig1, *fig2, *fig3, *fig4, *fig5;
	Color c;
	Point2D centre;
	Point2D width_height;
	Point2D resize_start, resize_end;
	Tree *mytree;
	double height, width;
	double thickness, resolution;
	double start_x, end_x, step_size; 
	double scale_x , scale_y;
	double randomnumber;
	int j, n, size;

	printf("Program is ruuning\n");
	//---------------------------Drawing f(x)-------------------------------------//
	width = 70.0 , height = 70.0;
	fig1 = start_figure(width, height);						//Creating figure start points
	c.red=0.0 , c.green=0.0,  c.blue=0.0;	
	set_color(fig1, c);										//Painting figure
	thickness=0.75, resolution=30;
	set_thickness_resolution(fig1, thickness, resolution);	//Settings

	start_x=-10.12, end_x=10.00, step_size=0.12;
	draw_fx(fig1, sin, start_x, end_x, step_size);		// Setting for y coordinates
	export_eps(fig1,"1fx.eps");

	//----------------------------Scaling Figure----------------------------------//
	scale_x = 3.0 , scale_y = 3.0;
	scale_figure(scale_x, scale_y, fig1);
	export_eps(fig1,"1fx_scaled.eps");
	
	//----------------------------Drawing Ellipse---------------------------------//
	width = 270.0 , height = 270.0;
	fig2 = start_figure(width, height);						//Creating figure start points
	c.red=10.0 ,  c.green=0.0, c.blue=0.0;	
	set_color(fig2, c);										//Painting figure
	thickness=0.75, resolution=30;
	set_thickness_resolution(fig2, thickness, resolution);	//Settings

	centre.x = 0.0, centre.y=0.0, width_height.x=24.0, width_height.y=7.0;
	draw_ellipse(&centre, &width_height, fig2);
	export_eps(fig2,"2ellipse.eps");

	//----------------------------Drawing Polyline-------------------------------//
	width = 150.0 , height = 150.0;
	fig3 = start_figure(width, height);						//Creating figure start points
	c.red=10.0 , c.green=55.0, c.blue=0.0;		
	set_color(fig3, c);										//Painting figure
	thickness=0.80, resolution=130;
	set_thickness_resolution(fig3, thickness, resolution);	//Settings
	randomnumber=3.4, j=0, n=6;
	Point2D poly_line[n];

	while(j<n){					//Change to create different polyline.
		poly_line[j].x = (2*j+randomnumber)*j;	
		poly_line[j].y = (j-5)*j*j;
		j++;
	}
	draw_polyline(poly_line, n, fig3);
	export_eps(fig3,"3polyline.eps");

	//----------------------------Resizing Figure-------------------------------//\.
	resize_start.x = -100.7  , resize_end.x = 100.18;
	resize_start.y = -100.4 , resize_end.y = 50.2;
	resize_figure(&resize_start, &resize_end, fig3);
	export_eps(fig3,"3polyline_resized.eps");	

	//----------------------------Drawing Polygon-------------------------------//
	width = 150.0 , height = 150.0;
	fig4 = start_figure(width, height);						//Creating figure start points
	c.red=0.0 , c.green=5.0, c.blue=0.0;		
	set_color(fig4, c);										//Painting figure
	thickness=0.75, resolution=30;
	set_thickness_resolution(fig4, thickness, resolution);	//Settings
	size = sizeof(poly_line)/sizeof(poly_line[0]);
	poly_line->size = size;    // I will store the size value in the struct.
	
	draw_polygon(poly_line, fig4);
	export_eps(fig4,"4polygon.eps");

	//-----------------------------Appending Figures----------------------------//
	append_figures(fig1,fig2);
	append_figures(fig2,fig3);
	append_figures(fig3,fig4);
	export_eps(fig1,"1-2-3-4_appended.eps");	
	//-----------------------------Drawing Trees--------------------------------//
	width = 1200.0 , height = 1900.0;
	fig5 = start_figure(width, height);						//Creating figure start points
	c.red=255.0 , c.green=0.0, c.blue=55.0;		
	set_color(fig5, c);										//Painting figure
	thickness=1.75, resolution=30;
	set_thickness_resolution(fig5, thickness, resolution);	//Settings

	mytree=NULL;   // It is not a binary search tree.
	insert(10, &mytree);
	insert(670,&mytree);
	insert(200,&mytree);
	insert(56, &mytree);
	insert(526,&mytree);
	insert(999,&mytree);
	insert(569,&mytree);

	draw_binary_tree(mytree,fig5);
	export_eps(fig5,"5binary_tree.eps");   
	resize_start.x = -1000.7  , resize_end.x = 1010.18;
	resize_start.y = -1000.4  , resize_end.y = 980.2;
	resize_figure(&resize_start, &resize_end, fig5);
	export_eps(fig5,"5binary_tree_resized.eps");   

	/* If figures are appended, it is enough to free just the first fig that appended !!!
	   The other may cause a problem.  */
	free_fig(fig1);
	free_fig(fig5);

	return 0;
}