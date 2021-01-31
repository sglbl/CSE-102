#include <stdio.h>
/*
img dosyasını txt okur gibi açıyosun sonra loopa girip eof a kdr değer alıyosun. 
değerleri decrypt_and_print fonkunda chardan int a çevirip 
decrypt_numbers fonkuna yolluyosun o da sana sembolü döndürüyo onu basıyosun
diğerleri de aynı aslında sadece ekstradan işlem yaptırıyo
*/
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

void decrypt_and_print (char* file_path){
	char buffer;
	int check,number_in_file;
	FILE *filep= fopen(file_path,"r");
	
	if (filep == NULL){
        printf("Couldn't open file\n");
        return;
    }
    check=fscanf(filep,"%c",&buffer);

    while(check != EOF ){
		check=fscanf(filep,"%c",&buffer);
		number_in_file=(int)buffer-48;
		printf("%c",decrypt_numbers(number_in_file));
	}

	fclose(filep);	
}



int main(){
	decrypt_and_print("encrypted_p1.img");

	return 0;
}