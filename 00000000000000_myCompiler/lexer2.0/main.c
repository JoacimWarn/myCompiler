

#include <stdio.h>
#include "lexer.h"

#define BUFFER		255
#define WORDSIZE	15
#define BUFFERPAR	32

//int isDigit(char*);
int str_cmp(char*, char*);
int isKeyWord(char*);
void printParBuffer(char*, FILE*);

int main(){
	
	printf("%d\n", isalnum('"'));
	
	int tab;
	char ch, buffer[WORDSIZE];
	char operators[] = "+-*/%=";
	FILE* fp;
	FILE* fpOut;
	
	int i, j, lparFlag;
	i = j = lparFlag = 0;
	
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
		
		if(lparFlag == 1 && ch != ')'){
			
			char bufferPar[BUFFERPAR];
			int counter = 0;
			
			do{
				
				bufferPar[counter++] = ch;
				
			}while((ch = fgetc(fp)) != ')');
			
			//read whole buffer until reaches ")"
			bufferPar[counter] = END_OF_FILE;
			counter = 0;
			
			printParBuffer(&bufferPar[0], fpOut);
			
		}
		
		lparFlag = 0;
		
		if(isalnum(ch)){
			
			buffer[j++] = ch;
			continue;
			
		}
		
		printf("%c", ch);
		
		switch(ch){
				
			case '"':
				while((ch = fgetc(fp)) != '"') fprintf(fpOut, "%c", ch);
				fprintf(fpOut, "\t\tstring\n");
				break;
				
			case LPAR:
				
				buffer[j] = END_OF_FILE;
				j = 0;
				lparFlag = 1;
				
				if(isKeyWord(buffer) == 1)						fprintf(fpOut, "%s\t\tKEYWORD\n", buffer);
				else if(!isKeyWord(buffer) && isDigit(buffer))	fprintf(fpOut, "%s\t\t%s\n", buffer, NUMBER);
				else if(ch != WSPACE)							fprintf(fpOut, "%s\t\t%s\n", buffer, IDENTIFIER);
				
				fprintf(fpOut, "%c\t\tLPAR\n", ch);
				break;
				
			case RPAR:
				fprintf(fpOut, "%c\t\tRPAR\n", ch);
				break;
				
			case LBRACKET:
				fprintf(fpOut, "%c\t\tLBRACKET\n", ch);
				break;
				
			case RBRACKET:
				fprintf(fpOut, "%c\t\tRBRACKET\n", ch);
				break;
				
			case ASSIGN:
				fprintf(fpOut, "%c\t\tASSIGN\n", ch);
				break;
				
			case PLUS:
				fprintf(fpOut, "%c\t\tPLUS\n", ch);
				break;
				
			case MINUS:
				fprintf(fpOut, "%c\t\tMINUS\n", ch);
				break;
				
			case TIMES:
				fprintf(fpOut, "%c\t\tTIMES\n", ch);
				break;
				
			case DIV:
				fprintf(fpOut, "%c\t\tDIV\n", ch);
				break;
				
			default:
				//read in whole buffer
				
				if((ch == WSPACE || ch == NEWLINE || ch == COMMA || ch == SEMI_COLON) && j != 0){
					
					buffer[j] = END_OF_FILE;
					j = 0;
					
					printf("%s", buffer);
					
					if(isKeyWord(buffer) == 1)						fprintf(fpOut, "%s\t\tKEYWORD\n", buffer);
					else if(!isKeyWord(buffer) && isDigit(buffer))	fprintf(fpOut, "%s\t\t%s\n", buffer, NUMBER);
					else if(ch == WSPACE)							fprintf(fpOut, "%s\t\t%s\n", buffer, IDENTIFIER);
					
				}
			
			break;
			
		}
		
	}
	
	fclose(fp);
	fclose(fpOut);
	return 0;
	
}

//prints expression in parenthesize to file
void printParBuffer(char* tempPtr, FILE* fpOut){
	
	int i;
	
	while(*tempPtr != END_OF_FILE){
		
		if(*tempPtr == '"'){
			//string
			*tempPtr++;
			
			while(*tempPtr != '"'){
				
				fprintf(fpOut, "%c", *tempPtr);
				*tempPtr++;
				
			}
			fprintf(fpOut, "\t\tstring\n");
			*tempPtr++;
			
		}
		else if(isalnum(*tempPtr)){
			//identifier
			char buffer[WORDSIZE];
			int counter = 0;
			
			while(isalnum(*tempPtr)){
				
				buffer[counter++] = *tempPtr++;
				
			}
			buffer[counter] = END_OF_FILE;
			
			fprintf(fpOut, "%s\t\t%s\n", buffer, IDENTIFIER);
			
		}
		else if(!isalnum(*tempPtr)){
			
			switch(*tempPtr){
				
				case PLUS:
					fprintf(fpOut, "%c\t\tPLUS\n", *tempPtr);
				break;
					
				case MINUS:
					fprintf(fpOut, "%c\t\tMINUS\n", *tempPtr);
				break;
					
				case TIMES:
					fprintf(fpOut, "%c\t\tTIMES\n", *tempPtr);
				break;
					
				case DIV:
					fprintf(fpOut, "%c\t\tDIV\n", *tempPtr);
				break;
				
			}
			
		}
		
		*tempPtr++;
		
	}
	
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
		
		if(*ptr >= '0' && *ptr <= '9') return 1;
		
		*ptr++;
		
	}
	
	return 0;
	
}
