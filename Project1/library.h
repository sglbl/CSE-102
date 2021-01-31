#ifndef _LIBRARY_H_
#define _LIBRARY_H_
/*
	This is the header file for EPS creating.
	Name-Surname: Suleyman Golbol
	Number: 1801042656
*/
typedef struct Color{
	double red;
	double green;
	double blue;
}Color;

typedef struct Point2D{
	double x,y;
	int size;
	struct Point2D* nextptr;
}Point2D;

typedef struct Tree{
	int data;
	struct Tree *left,*right;
}Tree;

typedef struct TreeValues{
	int data;
	Point2D point;
	struct TreeValues *nextptr;
}TreeValues;

typedef struct Figure{
	double thick, res;
	int counter;	// For tree.
	Tree *tree;
	Point2D max;
	Point2D min;
	TreeValues *treevalue;
	Point2D treear[30];
	double difx,dify;
	Point2D *currentPoint;
	Color col;
	struct Figure* nextptr;
}Figure;

/* Initializes the figure on canvas of a given dimension (width × height) */
Figure* start_figure(double width, double height);
/* Sets the thickness and resolution of the drawings to happen next. */
void set_thickness_resolution(Figure* fig, double thickness, double resolution);
/* Set the colour for the drawings to happen next.  */
void set_color(Figure* fig, Color c);
/* Draws the given function in the figure initialized. */
void draw_fx(Figure* fig, double f(double x), double start_x, double end_x, double step_size);
/* Draws a set of connected lines given in the array poly_line. */
void draw_polyline(Point2D * poly_line, int n, Figure* fig);
/* Draws a polygon between given coordinates and closes the loop by drawing a final line between first and the last point. */
void draw_polygon(Point2D * poly_line, Figure *fig);
/* Draws an ellipse centred around the centre with the given width and height. */
void draw_ellipse(Point2D * centre, Point2D * width_height, Figure* fig);
/* Scales the figure in both dimensions by scale_x and scale_y */
void scale_figure(double scale_x, double scale_y, Figure* fig);
/* Crops (may oversample) the given figure to be within a rectangle */
void resize_figure(Point2D *start_roi, Point2D *end_roi, Figure* fig);
/* Draws the given binary tree in the given canvas. */
void draw_binary_tree(Tree * root, Figure* fig);
/* Merges two figures and returns it in the first one. */
void append_figures(Figure * fig1, Figure * fig2);
/* Exports the current figure to an EPS file */
void export_eps(Figure * fig, char * file_name);
#endif