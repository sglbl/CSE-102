#include <stdio.h>
int decrypt_char (char character){
	switch(character){
		case ' ':
			return 0;
		case '-':
			return 1;
		case '_':
			return 2;
		case '|':
			return 3;
		case '/':
			return 4;
		case '\\':
			return 5;
		case 'O':
			return 6;
	}
}

void encrypt_messages(char* file_path){
	int number_i=0,number_i_j=0,buffer,buffer2,buffer3;
	char charbuffer;
	FILE *filep= fopen(file_path,"r");
	FILE *filep2= fopen("encrypted_p4.img","w");
	if(filep==NULL || filep2==NULL){
		printf("COuldn't open file.");
		return;
	}	
	/*buffers will be used for storing characters and numbers in memory*/
	buffer=0,buffer2=0,buffer3=0;  
	while(fscanf(filep, "%c", &charbuffer) == 1){
		fprintf(filep2,"%d",number_i);
		buffer3=buffer2;
		buffer2=buffer;

		if(charbuffer=='\n'){
			fprintf(filep2,"%c",charbuffer);
			buffer=0,buffer2=0,buffer3=0;
			fscanf(filep,"%c",&charbuffer);
			if(charbuffer=='\n'){
				fprintf(filep2,"%c",charbuffer);
				fscanf(filep,"%c",&charbuffer);
				fscanf(filep,"%c",&charbuffer);
			}
		}
		/*converting text to decrypted numbers.*/
		buffer=decrypt_char(charbuffer);

		number_i_j=buffer+buffer2+buffer3;
		number_i=number_i_j % 7;	
	}
	fclose(filep);
	fclose(filep2);
}

int main(){

	encrypt_messages("decrypted_p4.img");


	return 0;
}