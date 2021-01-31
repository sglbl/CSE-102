#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>	//For abs function
#define SIZE 100
#define ROWSIZE 100
#define PGONSIZE 22
#define PATHSIZE 15
#define PI 3.1415

typedef struct geometry{
	struct point{
		float pcoorx;
		float pcoory;
		char pname[3];
	}point;
	struct line{
		struct point p1;
		struct point p2;
		char lname[3][3];
	}line;
	struct pgon{
		struct line pgonline[PGONSIZE];
		struct point pgonpoint[PGONSIZE];
		char pgname[PGONSIZE][3];	//Line polygon name will be kept in pgname[21], point polygon will be kept in pgname[20]
	}pgon;
}Geometry;

typedef struct actions{
	char name[12];
	char comp1[3];
	char comp2[3];
	char trash[ROWSIZE];
}Action;

float area_line_polygon(Geometry Geo[SIZE], int until,int num){		//num was called by reference
	float result;
	int difference=num-until;	//Since when i made int f=num-until; it gives error.
	for(int f=difference;f<(num-1);f++){
		result += (Geo[num].pgon.pgonline[f].p1.pcoorx * Geo[num].pgon.pgonline[f].p2.pcoory -
				   Geo[num].pgon.pgonline[f].p2.pcoorx * Geo[num].pgon.pgonline[f].p1.pcoory);
	}
	result /= 2;
	return result;
}

float area_point_polygon(Geometry Geo[SIZE], int until,int num){	//num was called by reference
	float result;
	for(int f=0;f<until;f++){
		if(f==until-1)
			result += ( (Geo[num].pgon.pgonpoint[f].pcoorx * Geo[num].pgon.pgonpoint[0].pcoory) -
					    (Geo[num].pgon.pgonpoint[f].pcoory * Geo[num].pgon.pgonpoint[0].pcoorx) );		
		else
			result += ( (Geo[num].pgon.pgonpoint[f].pcoorx * Geo[num].pgon.pgonpoint[f+1].pcoory) -
					    (Geo[num].pgon.pgonpoint[f].pcoory * Geo[num].pgon.pgonpoint[f+1].pcoorx) );
	}
	result /= 2;
	return result;
}

float angle(float A_p1_x, float A_p1_y, float A_p2_x, float A_p2_y,  float B_p1_x, float B_p1_y, float B_p2_x, float B_p2_y){
	float result;
	float slope1= (A_p2_y - A_p1_y) / (A_p2_x - A_p1_x);
	float slope2= (B_p2_y - B_p1_y) / (B_p2_x - B_p1_x);

	result= fabs( atan ((slope2-slope1) / (1+(slope2*slope1)))  *(180/PI) );
	if( result != result ){
		result=90;  printf("assdsf\n");	}// That means result has NaN value which is perpendicular line(tan90 = ∞)
	return result ; 
}

float distance_point_and_line(float p1_x, float p1_y , float line_p1_x, float line_p1_y, float line_p2_x, float line_p2_y){
	/*	We should put p1_x and p1_y into the line as A*(p1_x) + B(p1_y) + C	*/
	float numerator = abs (  (line_p2_x - line_p1_x) * (line_p2_y - p1_y) - (line_p2_y - line_p1_y) * (line_p2_x - p1_x) );
	float denominator = sqrt( (line_p2_x - line_p1_x)*(line_p2_x - line_p1_x) + (line_p2_y - line_p1_y)*(line_p2_y - line_p1_y) );
	if(denominator>99999.9)		denominator=99999.9;	//To prevent floating point error.
	return 	numerator/denominator;
}

float find_distance(float p1_x, float p1_y, float p2_x, float p2_y){
	float square=(p2_y- p1_y)*(p2_y- p1_y) + (p2_x- p1_x)*(p2_x- p1_x);
	return sqrt(square);
}

void which_action(char buffer[][ROWSIZE], Geometry Geo[SIZE], int i, int polygon_point_data, int polygon_line_data){
	int until, count, a, f, coord1, coord2;
	size_t pathsize;
	char  path[PATHSIZE];
	float result;
	Action actbuffer[ROWSIZE];
	FILE *filep;

	for(int j=i; j<i+3; j++){
		if( strncmp(buffer[j],"actions",7) == 0 ){
			pathsize=strlen(buffer[j+1])-2;
			buffer[j+1][ strlen(buffer[j+1])-1]=0;
			strncpy(path, buffer[j+1], pathsize);	//Results will be printed to path file.
			filep=fopen(path,"w");	//Opening file that will be write to.
			if(filep==NULL){
				printf("Couldn't write file.\n");
				return;
			}
			until=atoi( buffer[j+2] );	//until times we will calculate operations.
			j +=3;
			for(int k=0; k<until; k++){
				sscanf(buffer[j+k],"%s %s %s %[/]",actbuffer[k].name,actbuffer[k].comp1, actbuffer[k].comp2, actbuffer[k].trash);
				//printf("%s %.3s %.3s \nTrash: %s\n",actbuffer[k].name,actbuffer[k].comp1, actbuffer[k].comp2, actbuffer[k].trash );
			}
			break;
		}
	}
	for(int k=0; k<until; k++){
		a=0, coord1=-1,coord2=-1, result=0;
		if ( strncmp(actbuffer[k].name,"Distance",8) == 0 &&    actbuffer[k].comp2[0] != 'L')  a=1;	//Distance between points
		else if ( strncmp(actbuffer[k].name,"Distance",8) == 0 && actbuffer[k].comp2[0]=='L')  a=2;	//Distance between line and point
		else if ( strncmp(actbuffer[k].name,"Angle",5) == 0)	a=3;
		else if ( strncmp(actbuffer[k].name,"Length",6) == 0 && actbuffer[k].comp1[0]=='L')            a=4; 
		else if ( strncmp(actbuffer[k].name,"Length",6) == 0 && strncmp(actbuffer[k].comp1,"PG",2)==0) a=5;
		else if ( strncmp(actbuffer[k].name,"Area",4) == 0)	    a=6;

		switch(a){
			case 1:
				for(int m=0; m<i; m++){
					if(strncmp(actbuffer[k].comp1, Geo[m].point.pname,2)==0 )
						coord1=m;
					if(strncmp(actbuffer[k].comp2, Geo[m].point.pname,2)==0 )
						coord2=m;
					if(coord1!=-1 && coord2!=-1){
						result=find_distance(Geo[coord1].point.pcoorx, Geo[coord1].point.pcoory, Geo[coord2].point.pcoorx, Geo[coord2].point.pcoory);
						break;
					}
				}
				fprintf(filep,"Distance(%s,%s) = %.1f\n",actbuffer[k].comp1,actbuffer[k].comp2,result);
				break;

			case 2:
				for(int m=0; m<i; m++){
					if(strncmp(actbuffer[k].comp1, Geo[m].point.pname,2)==0 )
						coord1=m;
					if(strncmp(actbuffer[k].comp2, Geo[m].line.lname[2],3)==0 )
						coord2=m;
					if(coord1!=-1 && coord2!=-1){
						result=distance_point_and_line( Geo[coord1].point.pcoorx, Geo[coord1].point.pcoory, Geo[coord2].line.p1.pcoorx,
													  Geo[coord2].line.p1.pcoory, Geo[coord2].line.p2.pcoorx, Geo[coord2].line.p2.pcoory );
						break;
					}
				}
				fprintf(filep,"Distance(%s,%.3s) = %.1f\n",actbuffer[k].comp1, actbuffer[k].comp2, result );
				break;

			case 3:
				for(int m=0; m<i; m++){
					if(strncmp(actbuffer[k].comp1, Geo[m].line.lname[2], 3)==0 )
						coord1=m;
					if(strncmp(actbuffer[k].comp2, Geo[m].line.lname[2], 3)==0 )
						coord2=m;
					
					if(coord1!=-1 && coord2!=-1){
							result=angle(Geo[coord1].line.p1.pcoorx, Geo[coord1].line.p1.pcoory, Geo[coord1].line.p2.pcoorx, Geo[coord1].line.p2.pcoory,
						    Geo[coord2].line.p1.pcoorx, Geo[coord2].line.p1.pcoory, Geo[coord2].line.p2.pcoorx, Geo[coord2].line.p2.pcoory);
							break;
					}
				}
				fprintf(filep,"Angle(%.3s,%.3s) = %.1f\n",actbuffer[k].comp1,actbuffer[k].comp2,result);
				break;

			case 4:
				for(int m=0; m<i; m++){
					if(strncmp(actbuffer[k].comp1, Geo[m].line.lname[2], 3)==0 ){
						result=find_distance(Geo[m].line.p1.pcoorx, Geo[m].line.p1.pcoory, Geo[m].line.p2.pcoorx, Geo[m].line.p2.pcoory);
						fprintf(filep,"Length(%.3s) = %.1f\n",Geo[m].line.lname[2], result);
						break;
					}
				}
				break;

			case 5:	 	//Length of polygons
				for(int m=0; m<i; m++){
					/*Length of polygon with points*/
					if(strncmp(actbuffer[k].comp1, Geo[m].pgon.pgname[20], 3)==0 ){	
						count=0;
						while(Geo[m].pgon.pgname[count][0] != '\0')	count++;
						count -= 1;
						for(int f=0;f<count;f++){
							if(f==count-1)
								result += find_distance(Geo[m].pgon.pgonpoint[f].pcoorx, Geo[m].pgon.pgonpoint[f].pcoory, 
											    Geo[m].pgon.pgonpoint[0].pcoorx, Geo[m].pgon.pgonpoint[0].pcoory);
							else
								result += find_distance(Geo[m].pgon.pgonpoint[f].pcoorx, Geo[m].pgon.pgonpoint[f].pcoory, 
												    Geo[m].pgon.pgonpoint[f+1].pcoorx, Geo[m].pgon.pgonpoint[f+1].pcoory);
						}
						fprintf(filep,"Length(%.3s) = %.1f\n",Geo[m].pgon.pgname[20],result );	
						break;
					}
					/*Length of polygon with lines*/
					else if( strncmp(actbuffer[k].comp1, Geo[m].pgon.pgname[21], 3)==0 ){		
						//printf("\nPolygon name is %s\n",Geo[m].pgon.pgname[21] );
						count=0;
						while(Geo[m].pgon.pgname[count][0] != '\0')
							count++;
						count--;
						f=0;
						while(Geo[m].pgon.pgonline[f].lname[2][0] == '\0')
							f++;

						for(int j=0;j<count; j++){
							//printf("Name %s\n",Geo[m].pgon.pgonline[f+j].lname[2] );
							//printf("Coor_1: (%.2f,%.2f)\n",Geo[m].pgon.pgonline[f+j].p1.pcoorx, Geo[m].pgon.pgonline[f+j].p1.pcoory);
							//printf("Coor_2: (%.2f,%.2f)\n",Geo[m].pgon.pgonline[f+j].p2.pcoorx, Geo[m].pgon.pgonline[f+j].p2.pcoory);
							result += find_distance(Geo[m].pgon.pgonline[f+j].p1.pcoorx, Geo[m].pgon.pgonline[f+j].p1.pcoory, 
											   Geo[m].pgon.pgonline[f+j].p2.pcoorx, Geo[m].pgon.pgonline[f+j].p2.pcoory);
						}
						fprintf(filep,"Length(%.3s) = %.1f\n",Geo[m].pgon.pgname[21],result);
						break;
					}
				}
				break;

			case 6:	//Area of a polygon
				for(int m=0; m<i; m++){
					/*Area of polygon with points*/
					if(strncmp(actbuffer[k].comp1, Geo[m].pgon.pgname[20], 3)==0 ){	
						count=0;
						while(Geo[m].pgon.pgname[count][0] != '\0')
							count++;
						
						count--;
						result=area_point_polygon(Geo, count, polygon_point_data);
						fprintf(filep,"Area(%.3s) = %.1f\n",Geo[polygon_point_data].pgon.pgname[count], result);

					}
					/*Area of polygon with lines*/
					else if(strncmp(actbuffer[k].comp1, Geo[m].pgon.pgname[21], 3)==0 ){
						count=0;
						while(Geo[m].pgon.pgname[count][0] != '\0')
							count++;
						result=area_line_polygon(Geo, count, m);
						fprintf(filep,"Area(%.3s) = %.1f\n",Geo[m].pgon.pgname[count-1], result);
					}

				}
				break;
			default:
				fprintf(filep,"NOT_IMPLEMENTED\n");

		}

	}
	printf("Program is running.\n");
	fclose(filep);
}

void polygon_with_points(char buffer[][ROWSIZE], Geometry Geo[SIZE], int i,int *lettercounter){
		char *piece;
		int k;
		for(int j=0;j<60;j++){	//For polygon with points
			piece=strtok(buffer[i]," ");
			strncpy(Geo[i].pgon.pgname[0],piece,2);
			for(int m=0;m<*lettercounter+1;m++){	
				if( strncmp(Geo[m].point.pname,Geo[i].pgon.pgname[0],3)==0 ){	//If polygon name==pointname then we found coordinates.
					Geo[i].pgon.pgonpoint[0].pcoorx= Geo[m].point.pcoorx;
					Geo[i].pgon.pgonpoint[0].pcoory= Geo[m].point.pcoory;
				}
			}
			k=1;
			while( piece!= NULL ){
				piece=strtok(NULL," ");
				strncpy(Geo[i].pgon.pgname[k],piece,2);
				for(int m=0;m<*lettercounter+1;m++){					
					if( strncmp(Geo[m].point.pname,Geo[i].pgon.pgname[k],3)==0 ){	//If polygon name==pointname then we found coordinates.
						Geo[i].pgon.pgonpoint[k].pcoorx= Geo[m].point.pcoorx;
						Geo[i].pgon.pgonpoint[k].pcoory= Geo[m].point.pcoory;
						//printf("pname %s and pgname %s\n",Geo[m].point.pname,Geo[i].pgon.pgname[k]);
						//printf("Coor:(%.2f,%.2f)\n",Geo[i].pgon.pgonpoint[k].pcoorx,Geo[i].pgon.pgonpoint[k].pcoory);
					}
				}
				k++;
				if(k==*lettercounter-1){		//Finding polygon name which has 3 characters.
					piece=strtok(NULL," ");
					//printf("Name of polygon is %s \n",piece);
					strncpy(Geo[i].pgon.pgname[k],piece,3);
					strncpy(Geo[i].pgon.pgname[20],piece,3);
					break;
				}
			}
			break;	
		}	
}

void polygon_with_lines(char buffer[][ROWSIZE], Geometry Geo[SIZE], int i,int *lettercounter){
	char *piece;
	int k=0;
	piece=strtok(buffer[i]," ");
	strncpy(Geo[i].pgon.pgname[k], piece, 3);	//Copying the name of the polygon pieces.
	for(int m=0;m<20;m++){	
		if( strcmp( Geo[m].line.lname[2], Geo[i].pgon.pgname[k] )==0 ){
			strncpy(Geo[i].pgon.pgonline[m].lname[0], Geo[m].line.lname[0],2);	//Copying point infos
			strncpy(Geo[i].pgon.pgonline[m].lname[1], Geo[m].line.lname[1],2);
			strncpy(Geo[i].pgon.pgonline[m].lname[2], Geo[m].line.lname[2],3);
			Geo[i].pgon.pgonline[m].p1.pcoorx= Geo[m].line.p1.pcoorx;		//Copying point coordinates to polygon.
			Geo[i].pgon.pgonline[m].p1.pcoory= Geo[m].line.p1.pcoory;
			Geo[i].pgon.pgonline[m].p2.pcoorx= Geo[m].line.p2.pcoorx;
			Geo[i].pgon.pgonline[m].p2.pcoory= Geo[m].line.p2.pcoory;
		}
	}
	k=1;
	while( piece!= NULL ){
		piece=strtok(NULL," ");
		strncpy(Geo[i].pgon.pgname[k], piece, 3);
		for(int m=0;m<20;m++){	
			if( strncmp( Geo[m].line.lname[2], Geo[i].pgon.pgname[k],3 )==0 ){
				//printf("Line name %s ",Geo[m].line.lname[2] );
				strncpy(Geo[i].pgon.pgonline[m].lname[0], Geo[m].line.lname[0],2);	//Copying point infos
				strncpy(Geo[i].pgon.pgonline[m].lname[1], Geo[m].line.lname[1],2);
				strncpy(Geo[i].pgon.pgonline[m].lname[2], Geo[m].line.lname[2],3);
				Geo[i].pgon.pgonline[m].p1.pcoorx= Geo[m].line.p1.pcoorx;		//Copying point coordinates to polygon.
				Geo[i].pgon.pgonline[m].p1.pcoory= Geo[m].line.p1.pcoory;
				Geo[i].pgon.pgonline[m].p2.pcoorx= Geo[m].line.p2.pcoorx;
				Geo[i].pgon.pgonline[m].p2.pcoory= Geo[m].line.p2.pcoory;
			}
		}
		k++;
		if(piece[0]=='P' && piece[1]=='G'){
			strncpy(Geo[i].pgon.pgname[21],piece,3);
			//printf("\nPolygon name is %s\n",Geo[i].pgon.pgname[21] );
			break;
		}

	}	
}

void process(char buffer[][ROWSIZE],int size,int until){
	int i=2;
	int lettercounter, polygon_point_data, polygon_line_data;
	char trash[i][ROWSIZE];
	Geometry Geo[SIZE];	

	while(i<until-1){	
		if(buffer[i][0]!='L' && buffer[i][0]!='P'){		//Seperating point coordinates and names.
			sscanf(buffer[i],"%f %f %s %[/]",&Geo[i].point.pcoorx, &Geo[i].point.pcoory, Geo[i].point.pname, trash[i]);
			//printf("Point is (%.2f , %.2f)  \tName: %s\n",Geo[i].point.pcoorx, Geo[i].point.pcoory, Geo[i].point.pname);
		}
		
		if(buffer[i][0]=='P'){	//For line	(Points will be stored and will be use to create lines.)
			for(int j=0; j<i ;j++){
				if( strncmp(Geo[j].point.pname,buffer[i],2)==0 ){
					sscanf(buffer[i],"%s %s %s %[/]",Geo[i].line.lname[0], Geo[i].line.lname[1], Geo[i].line.lname[2], trash[i]);
					//printf("Line-> %s %s %s\n",Geo[i].line.lname[0], Geo[i].line.lname[1], Geo[i].line.lname[2]);
					for(int m=0;m<i;m++){
						if(strncmp( Geo[m].point.pname , Geo[i].line.lname[0],3 )==0 ){
							Geo[i].line.p1.pcoorx= Geo[m].point.pcoorx;
							Geo[i].line.p1.pcoory= Geo[m].point.pcoory;
						}
						else if(strncmp( Geo[m].point.pname , Geo[i].line.lname[1],3 )==0 ){
							Geo[i].line.p2.pcoorx= Geo[m].point.pcoorx;
							Geo[i].line.p2.pcoory= Geo[m].point.pcoory;
						}
					}
					break;
				}
			}
		}
		//For polygon with points
		lettercounter=0;	 
		for(int j=0;j<60;j++){			//j is for which char in a row (for polygon with points)
			if(buffer[i][j]=='P')
				lettercounter++;  // Number of line components in polygon

			if(buffer[i][0]=='P' && buffer[i][j]=='P' && buffer[i][j+1]=='G' ){	//For polygon with points
				polygon_point_data=i;
				polygon_with_points(buffer, Geo, polygon_point_data,&lettercounter); 
			}
		}
		//For polygon with lines
		if(buffer[i][0]=='L'){
			polygon_line_data=i;
			polygon_with_lines(buffer, Geo, polygon_line_data, &lettercounter);
		}
		i++;

	}
	which_action(buffer,Geo,i, polygon_point_data, polygon_line_data);
}

void read_commands(){
	char buffer[SIZE][ROWSIZE];
	int buf,datasize,i;
	FILE *filep=fopen("commands.txt","r");
	if(filep==NULL){
		printf("Couldn't read file.");
		return;
	}
	i=0;
	while( fgets(buffer[i],SIZE,filep)!=0 ){
		if( strncmp(buffer[i],"data",4) == 0 ){
			fscanf(filep," %d",&buf);
			i++;
			for(int j=0; j<buf+1 ; j++,i++)
				fgets(buffer[i],SIZE,filep);
		}

		if( strncmp(buffer[i],"actions",7) == 0 )
			datasize=i;
		i++;
	}
	
	fclose(filep);
	process(buffer,SIZE,datasize);
}

int main(){
	read_commands();
	return 0;
}