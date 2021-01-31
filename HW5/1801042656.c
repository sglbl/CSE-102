#include <stdio.h>

void append_file(char* file_path, char c){
	int intc;
	FILE *filep = fopen(file_path,"a");
	if (filep == NULL)
		return;
	fprintf(filep,"%c",c);
    fclose(filep);
}

int check_reiteration(char buffer){	//My helper function that checks reiterations
	int flag=0;
	char name=buffer;
	FILE *filep=fopen("readed_news_id.txt","r");
	if (filep == NULL)
		return 0;
	while( fscanf(filep,"%c",&buffer) != EOF ){
		if(buffer==name) flag=1;
	}

	fclose(filep);
	if(flag==1)		 return 1;
	else if(flag==0) return 0;
}

void readed_files(){  //My helper function to print readed news.
	char buffer,bufferforReiteration[6];
	int count1=0,count2=0,count3=0,count4=0;
	FILE *filep=fopen("readed_news_id.txt","r");
	if (filep == NULL)
		return;

	while( fscanf(filep,"%c",&buffer) != EOF ){
		switch(buffer){
			case '1': count1=1;
					  break;
			case '2': count2=1;
					  break;
			case '3': count3=1;
					  break;
			case '4': count4=1;
					  break;
			//No need to default becase in readed_news_id file can't contain other characters.
		}
	}
	if(count1==1)	printf("1.new is readed.\n");
	if(count2==1)	printf("2.new is readed.\n");
	if(count3==1)	printf("3.new is readed.\n");
	if(count4==1)	printf("4.new is readed.\n");

	fclose(filep);
}

void read_news(char buffer[500], char file_path[10], int is_Only_Title){
	int check=1,j=0;
	FILE *filep = fopen(file_path,"r");
	if (filep == NULL){
        printf("There is no such a text\n");
        return;
    }
	while(check != EOF){
			check=fscanf(filep,"%c",&buffer[j]);
			printf("%c",buffer[j]);
			if(buffer[j] == '\n' && is_Only_Title==1)	break;
			j++;			
	}
	fclose(filep);
}
	/*	PART3	*/
double f_func(int x){
	return ( (x*x*x) - (x*x) +2 )*1.0;
}
double g_func(double f(int x), int a){
	return f(a)*f(a);
}

void read_magic_numbers(char buffer_magic[10], char buffer_news[500]){
	int i,a;
	FILE *filep=fopen(buffer_magic,"r");
	if (filep == NULL)   return;
	
	double result=0;
	for (i=0; fscanf(filep,"%c",&buffer_news[i]) != EOF ;i++){
		if(buffer_news[i]== '#'){
			fscanf(filep,"%d",&a);	//To get the integer after #
			result += g_func(f_func,a);	//They will sum up n times.
		}
	}
	printf("%.2lf\n",result);
	fclose(filep);
}

void menu(){
	char which,choice,choice2,buffer[500],namebuffer[20];
	int is_Only_Title=1,newsId,check=1,OneorZero;

	FILE *filep = fopen("all_news_id.txt","r");
	if (filep == NULL){
        printf("Couldn't open file\n");
        return;
    }
	printf("**********Daily Press**********\n");
	/*      	TITLE of NEWS 			*/
	while(fscanf(filep,"%d",&newsId) != EOF ){
		printf("Title of %d. news: ",newsId);
		/*	Using sprintf to change the name of the file_path and prevent unnecessary code	*/
		sprintf(namebuffer,"news/%d.txt",newsId);  
		read_news(buffer,namebuffer,is_Only_Title);
	}

	while(check==1){
		printf("\nWhat do you want to do?\n");
		printf("a.Read a news\nb.List the readed news\nc.Get encrypted information from the news\n");
		scanf(" %c",&choice);
		switch(choice){
			case 'a':
				printf("Which text do you want to read?\n");
				scanf(" %c",&which);
				if(check_reiteration(which) == 1 ){
					printf("This new is readed. Do you want to read it again? Yes(1)/No(0)\n");
					while(scanf("%d",&OneorZero) !=1 && getchar()!='\n') //To prevent infinite loop
						printf("Unsupported character.Enter again: ");

					while(OneorZero!=1 && OneorZero!=0){
						printf("You entered wrong input.Try again.");
						while(scanf("%d",&OneorZero) !=1 && getchar()!='\n') //To prevent infinite loop
							printf("Unsupported character.Enter again: ");
					}
						if(OneorZero==0){
							printf("Do you want to continue? Yes(y)/No(n)");
							scanf(" %c",&which);
							if(which=='n'){
								printf("Goodbye");
								return;
							}
							else if(which=='y')
								break;
							else{
								printf("You entered wrong input.\n");
								break;
							}
						}

				}
				/* I will use "readed_news_id.txt" file to write which texts were readed.
				   Because of that, in beginning file is empty (it doesn't contain '2' character.) */
				if(which=='1' || which=='2' || which=='3' || which=='4')
					append_file("readed_news_id.txt", which);		//writing to text.
				/*	Changing the name of the file_path due to text number	*/
				sprintf(namebuffer,"news/%d.txt",(int)which-48);	
				is_Only_Title=0;
				read_news(buffer, namebuffer, is_Only_Title);

				printf("\n\nDo you want to continue? Yes(y)/No(n)\n");
				scanf(" %c",&choice2);
				if(choice2=='n')	 check=0;
				else if(choice2!= 'n' && choice2!= 'y')		printf("WRONG INPUT. TRY AGAIN!");
				break;
				
			case 'b':
				printf("Readed news are listed below.\n");
				readed_files();

				printf("\nDo you want to continue? Yes(y)/No(n)\n");
				scanf(" %c",&choice2);
				if(choice2=='n')	 check=0;
				else if(choice2!= 'n' && choice2!= 'y')		printf("WRONG INPUT. TRY AGAIN!");
				break;

			case 'c':
				printf("Which text would you like to decrypt?\n");
				scanf(" %c",&which);
				while(which!='1' && which!='2' && which!='3' && which!='4'){
					printf("Wrong input. Try again:\n");
					scanf(" %c",&which);
				}
				sprintf(namebuffer,"news/%c.txt",which);  //Changing the name of filepath to prevent unnecessary code
				read_news(buffer, namebuffer, 0);
				switch (which){
					case '1':
						printf("\nThe number of tests performed: ");
						break;
					case '2':
						printf("\nThe number of sick people: ");
						break;
					case '3':
						printf("\nThe number of deaths: ");
						break;
					case '4':
						printf("\nExpected number of sick people: ");
						break;
					//No need to default becase which has to be one of these 4 char.
				}
				read_magic_numbers(namebuffer, buffer);
				printf("Do you want to continue? Yes(y)/No(n)\n");
				scanf(" %c",&choice2);
				if(choice2=='n')	 check=0;
				else if(choice2!= 'n' && choice2!= 'y')		printf("WRONG INPUT. TRY AGAIN!");
				break;

			default:
				printf("You entered wrong input. Try again:\n");
		}
	}

	fclose(filep);
}

int main(){
	menu();
	return 0;
}