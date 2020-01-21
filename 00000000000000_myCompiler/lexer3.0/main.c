

#include <stdio.h>
#include "lexer.h"

#define is_digit(c) ('0' <= (c) && (c) <= '9')

#define BUFFER		255
#define WORDSIZE	15
#define BUFFERPAR	32

//int isDigit(char*);
int str_cmp(char*, char*);
int isKeyWord(char*);
void printParBuffer(char*, FILE*);

void printBuffer(char* buffer, FILE* fpOut){
	
	if(isKeyWord(buffer) == 1)						fprintf(fpOut, "%s\t\tKEYWORD\n", buffer);
	else if(!isKeyWord(buffer) && isDigit(buffer))	fprintf(fpOut, "%s\t\t%s\n", buffer, NUMBER);
	else if(*buffer != WSPACE)						fprintf(fpOut, "%s\t\t%s\n", buffer, IDENTIFIER);
	
}

int main(){
	
	printf("%d\n", isalnum('"'));
	
	int nrOfParents, nrOfBrackets;
	char ch, buffer[WORDSIZE];
	char operators[] = "+-*/=";
	FILE* fp;
	FILE* fpOut;
	
	int i, j;
	i = j = nrOfParents = nrOfBrackets = 0;
	
	fp = fopen("expr.txt","r");
	
	if(fp == NULL){
		
		printf("error while opening file\n");
		return 1;
		
	}
	
	fpOut = fopen("outputLexer.txt", "w");
	
	if(fpOut == NULL){
		
		fprintf(stderr, "\nError opening file...");
		fclose(fp);
		return 1;
		
	}
	
	//reading source file
	while((ch = fgetc(fp)) != EOF){
		
		if(!isalnum(ch)) for(i = 0; i < 5; i++) if(operators[i] == ch){
			
			fprintf(fpOut, "%c\t\tOP\n", ch);
			continue;
			
		}
		if(isalnum(ch)) buffer[j++] = ch;
		else{
			
			switch(ch){
				
			case STRING:
				while((ch = fgetc(fp)) != '"') fprintf(fpOut, "%c", ch);
				fprintf(fpOut, "\t\tSTRING\n");
				break;
				
			case LPAR:
				if(j != 0){
					
					buffer[j] = END_OF_FILE;
					j = 0;
					printBuffer(buffer, fpOut);
					
				}
				
				fprintf(fpOut, "%c\t\tLPAR\n", ch);
				nrOfParents++;
				break;
				
			case RPAR:
				if(j != 0){
					
					buffer[j] = END_OF_FILE;
					j = 0;
					printBuffer(buffer, fpOut);
					
				}
				
				fprintf(fpOut, "%c\t\tRPAR\n", ch);
				nrOfParents--;
				break;
				
			case LBRACKET:
				fprintf(fpOut, "%c\t\tLBRACKET\n", ch);
				nrOfBrackets++;
				break;
				
			case RBRACKET:
				fprintf(fpOut, "%c\t\tRBRACKET\n", ch);
				nrOfBrackets--;
				break;
				
			case COMMA:
				if(j != 0){
					
					buffer[j] = END_OF_FILE;
					j = 0;
					printBuffer(buffer, fpOut);
					
				}
				
				fprintf(fpOut, "%c\t\tCOMMA\n", ch);
				
				break;
				
			case SEMI_COLON:
				if(j != 0){
					
					buffer[j] = END_OF_FILE;
					j = 0;
					printBuffer(buffer, fpOut);
					
				}
				
				fprintf(fpOut, "%c\t\tSEMI_COLON\n", ch);
				break;
				
			case WSPACE:
				buffer[j] = END_OF_FILE;
				
				if(j > 0) printBuffer(buffer, fpOut);
				j = 0;
				break;
				
			default:
				break;
				
			}
			
			buffer[j] = END_OF_FILE;
			j = 0;
			
			//printf("%s", buffer);
			
		}
		
		printf("%c", ch);
		
	}
	
	if( nrOfParents != 0) printf("\nToo many or too little parentheses");
	if(nrOfBrackets != 0) printf("\nToo many or too little brackets");
	
	fclose(fp);
	fclose(fpOut);
	return 0;
	
}

//return 1 if buffer is a keyword
int isKeyWord(char* buffer){
	
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
		"do","double","else","enum","extern","float","for","goto",
		"if","int","long","register","return","short","signed",
		"sizeof","static","struct","switch","typedef","union",
		"unsigned","void","volatile","while"};
	
	int i, flag;
	flag = 0;
	
	for(i = 0; i < 32; i++){
		
		if(str_cmp(keywords[i], buffer) == 0){
			
			flag = 1;
			break;
			
		}
		
	}
	
	return flag;
	
}

//return 0 if same word
int str_cmp(char* s, char* t){
	
	while(*s == *t){
		
		if(*s == '\0' && *t == '\0') return 0;
		
		*s++;
		*t++;
		
	}
	
	return 1;
	
}

//return 1 if is digit
int isDigit(char* temp){
	
	char* ptr;
	ptr = temp;
	
	while(*ptr){
		
		if(!(*ptr >= '0' && *ptr <= '9')) return 0;
		
		*ptr++;
		
	}
	
	return 1;
	
}
