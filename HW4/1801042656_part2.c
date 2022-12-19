#include <stdio.h>

char decrypt_numbers (int number){
	switch(number){
		case 0:
			return ' ';
		case 1:
			return '-';
		case 2:
			return '_';
		case 3:
			return '|';
		case 4:
			return '/';
		case 5:
			return '\\';
		case 6:
			return 'O';
		default:
			return '\n';
	}
}

void deep_decrypt_and_print(char* file_path){
	char buffer,buffer2,buffer3;
	int check,number_i_j=0,count=0;
	FILE *filep= fopen(file_path,"r");
	if(filep==NULL){
		printf("COuldn't open file.");
		return;
	}	
	check=fscanf(filep,"%c",&buffer);
	fscanf(filep,"%c",&buffer);
	buffer2=buffer;
	fscanf(filep,"%c",&buffer);
	buffer3=buffer;
		
	while(check != EOF){

		number_i_j=0;
		if(count != 0){
			buffer2=buffer3;
			buffer3=buffer;
		}
		count++;

		check=fscanf(filep,"%c",&buffer);
		

		number_i_j = (int)buffer + (int)buffer2 + (int)buffer3 -48*3;

			if(buffer=='\n'){
				fscanf(filep,"%c",&buffer);
				buffer2=buffer;
				fscanf(filep,"%c",&buffer);
				buffer3=buffer;
				fscanf(filep,"%c",&buffer);
			}   
		
		number_i_j = number_i_j % 7;
		printf("%c",decrypt_numbers(number_i_j));
		
	}
	fclose(filep);
}





int main(){
	deep_decrypt_and_print("encrypted_p2.img");

	return 0;
}