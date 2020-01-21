#include <stdio.h>

#define BUFFER 255

int main(){
	
	FILE* fp;
	char text[BUFFER];
	char word[BUFFER];
	int c, i;
	
	fp = fopen("test.txt", "r");
	
	i = 0;
	
	while((c = getc(fp)) != EOF){
		
		text[i] = c;
		
		printf("%c %c\n", text[i], c);
		i++;
		if(c == '\n'){
			
			printf("%s", text);
			for(; i > 0; i--) text[i] = '\0';
			
		}
		
	}
	
	//printf("%s", text);
	
	return 0;
	
}