#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#include <time.h>

#define BUFFER 100

#define is_digit(c) ('0' <= c && c <= '9')
#define ushort unsigned short int

struct tree{
	
	struct tree* left;
	struct tree* right;
	
	int level;
	
	struct statement* stmt;
	struct expression* exp;
	
};

struct statement{
	
	struct statement* next;
	
	struct expression* exp;
	
};

struct expression{
	
	struct expression* left;
	struct expression* right;
	char type;		/* D or P or I */
	int value;		/* for D */
	char operator;	/* for P */
	char operands;	/* for P if already has two operands */
	
};

struct tree* addNewNode(struct tree*, struct expression*, int);
struct expression* addNewElement(struct expression*, char);
void printBottomUpTree(struct tree*);

char* infixToPostfixReverse(char*);
char* buildExpression(char*);
void printBottomUp(struct expression*);
void checkOperands(struct expression*);
int isKeyWord(char*);
int str_cmp(char*, char*);

//adds a new node to the tree struct
struct tree* addNewNode(struct tree* temp, struct expression* expr, int tab){
	
	if(temp == NULL){
		
		temp = (struct tree*) malloc(sizeof(struct tree));
		
		temp->exp = expr;
		temp->level = tab;
		temp->stmt = NULL;
		temp->left  = NULL;
		temp->right = NULL;
		
	}
	else{
		
		if(temp->right == NULL){
			
			tab++;
			temp->right = addNewNode(temp->right, expr, tab);
			
		}
		else if(temp->left == NULL){
			
			tab++;
			temp->left = addNewNode(temp->left, expr, tab);
			
		}
		else{
			
			//if random -> 0 then go left, else go right
			
			int random = (rand() % (1 - 0 + 1)) + 0;
			
			if(random < 1){
				
				tab++;
				temp->left = addNewNode(temp->left, expr, tab);
				
			}
			else{
				
				tab++;
				temp->right = addNewNode(temp->right, expr, tab);
				
			}
			
		}
		
	}
	
	return temp;
	
}

void printBottomUpTree(struct tree* temp){
	
	if(temp == NULL) return;
	
	printBottomUpTree(temp->right);
	
	printBottomUpTree(temp->left);
	
	printBottomUp(temp->exp);
	
}





void printExpressionToFile(FILE* fpOut, struct expression* temp, int tab){
	
	if(temp == NULL) return;
	
	printExpressionToFile(fpOut, temp->right, tab);
	
	printExpressionToFile(fpOut, temp->left, tab);
	
	int i;
	
	for(i = 0; i < tab; i++) fprintf(fpOut, "\t");
	
	fprintf(fpOut, "op:%c val:%c type:%c\n", temp->operator, temp->value, temp->type);
	
}

void printTreeToFile(FILE* fpOut, struct tree* temp){
	
	//varje nivå vi går ner -->> tab++
	
	if(temp == NULL) return;
	
	printTreeToFile(fpOut, temp->right);
	
	printTreeToFile(fpOut, temp->left);
	
	fprintf(fpOut, "\n");
	
	printExpressionToFile(fpOut, temp->exp, temp->level);
	
}






int main(){
	
	int tab = 0;
	tab = tab + '\t';
	
	printf("hej %c hej", tab );
	
	srand(time(0));
	
	FILE* fpRead;
	FILE* fpWrite;
	int ch, i;
	char buffer[BUFFER];
	
	i =  0;
	
	fpRead = fopen("stmt.txt", "r");
	
	if(fpRead == NULL){
		
		printf("Error opening file\n");
		return 1;
		
	}
	
	fpWrite = fopen("outputParser.txt", "w");
	
	if(fpWrite == NULL){
		
		printf("Error opening file\n");
		fclose(fpRead);
		return 1;
		
	}
	
	/*
	while((ch = fgetc(fpRead)) != EOF){
		
		fprintf(fpWrite, "%c", ch);
		printf("%c", ch);
		
		if(ch == SEMI_COLON){
			
			buffer[i] = END_OF_FILE;
			i = 0;
			
		}
		
		buffer[i++] = ch;
		
	}
	*/
	
	struct expression* root = NULL;
	root = addNewElement(root, '=');
	root = addNewElement(root, '+');
	root = addNewElement(root, '/');
	root = addNewElement(root, '-');
	
	root = addNewElement(root, '1');
	root = addNewElement(root, '3');
	checkOperands(root);
	root = addNewElement(root, '2');
	checkOperands(root);
	root = addNewElement(root, 'a');
	checkOperands(root);
	root = addNewElement(root, 'a');
	
	//printBottomUp(root);
	
	struct expression* test = NULL;
	test = addNewElement(test, '=');
	test = addNewElement(test, '+');
	
	test = addNewElement(test, '1');
	test = addNewElement(test, '/');
	
	test = addNewElement(test, '2');
	test = addNewElement(test, '*');
	
	test = addNewElement(test, '3');
	test = addNewElement(test, 'c');
	checkOperands(test);
	test = addNewElement(test, 'c');
	checkOperands(test);
	
	//printBottomUp(test);
	
	struct tree* theTree = NULL;
	
	//theTree = addNewNode(theTree, test);
	
	//printBottomUp(theTree->exp);
	
	for(i = 0; i < 10; i++){
		
		theTree = addNewNode(theTree, root, 1);
		
	}
	
	printTreeToFile(fpWrite, theTree);
	
	fclose(fpRead);
	fclose(fpWrite);
	
	//printBottomUpTree(theTree);
	
	//printBottomUp(theTree->exp);
	
	//char* a = "a = a + 2 / (3-1)\0";
	//char* theExpression;
	//theExpression = buildExpression(a);
	//printf("%s", theExpression);
	//evaluateExpression(expression);
	//root->exprPtr = buildExpression(root->exprPtr, a);
	
	printf("\nPress any key to terminate...");
	getch();
	
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

struct expression* addNewElement(struct expression* temp, char data){
	
	if(temp == NULL){
		
		//empty node, create new expression node
		temp = (struct expression*) malloc(sizeof(struct expression));
		
		if(!isalnum(data) && !isdigit(data)){
			
			temp->type = 'P';
			temp->value = END_OF_FILE;
			temp->operator = data;
			temp->operands = '0';
			
		}
		else{
			
			if(!isdigit(data))temp->type = 'I';
			else			  temp->type = 'D';
			temp->value = data;
			temp->operator = END_OF_FILE;
			temp->operands = END_OF_FILE;
			
		}
		
		//temp->value = END_OF_FILE;
		//temp->operator = data;
		temp->left = NULL;
		temp->right = NULL;
		
	}
	else{
		
		if(!isalnum(data) && !isdigit(data)){
			//operator
			if(temp->right == 0) temp->right = addNewElement(temp->right, data);
			else{
				
				if(temp->right->type == 'D' && temp->left == 0){
					
					temp->left = addNewElement(temp->left, data);
					
				}
				else if(temp->right->type == 'D' && temp->left != 0){
					
					if(temp->left->type == 'P' && temp->left->operands == '0'){
						
						temp->left = addNewElement(temp->left, data);
						
					}
					
				}
				else if(temp->right->type == 'P' && temp->right->operands == '0'){
					
					temp->right = addNewElement(temp->right, data);
					
				}
				
			}
			
		}
		else{
			
			//digit or identifier
			if(temp->type == 'P' && temp->right != 0){
				
				if(temp->right->type == 'D'){
					
					temp->left = addNewElement(temp->left, data);
					
				}
				else if(temp->right->type == 'P' && temp->right->operands == '0'){
					
					temp->right = addNewElement(temp->right, data);
					
				}
				else if(temp->right->type == 'P' && temp->right->operands == '1'){
					
					temp->left = addNewElement(temp->left, data);
					
				}
				
			}
			else if(temp->type == 'P' && temp->right == 0){
				
				//right node is empty, allocate it
				temp->right = addNewElement(temp->right, data);
				
			}
			
		}
		
	}
	
	return temp;
	
}

void checkOperands(struct expression* temp){
	
	if(temp == NULL) return;
	
	checkOperands(temp->right);
	
	checkOperands(temp->left);
	
	if(temp->type == 'P'){
		
		if(temp->right != 0){
			
			if(temp->left != 0){
				
				if((temp->right->type == 'D' || temp->right->type == 'I' || temp->right->operands == '1') && (temp->left->type == 'D' || temp->left->type == 'I' || temp->left->operands == '1')) temp->operands = '1';
				
			}
			
		}
		
	}
	
}

/* Prints out tree structure from bottom up */
void printBottomUp(struct expression* temp){
	
	if(temp == NULL) return;
	
	printBottomUp(temp->right);
	
	printBottomUp(temp->left);
	
	printf("op:%c val:%c type:%c\n", temp->operator, temp->value, temp->type);
	
}

/* returns expression in postfix and also reverses the expression */
char* infixToPostfixReverse(char* buffer){
	
	char* startPtr;
	startPtr = buffer;
	
	int size = 10;
	
	char leftStack[size], rightStack[size];
	int left, right, oper;
	left = right = 0;
	
	while(*buffer){
		
		if(isalnum(*buffer)){
			
			leftStack[left++] = *buffer;
			leftStack[left] = END_OF_FILE;
			
		}
		else if(*buffer != WSPACE){
			
			if(right == 0){
				
				rightStack[right++] = *buffer;
				rightStack[right] = END_OF_FILE;
				
			}
			else{
				
				if((rightStack[right-1] == DIV || rightStack[right-1] == TIMES) && (*buffer == TIMES || *buffer == DIV)){
					
					//move element from top of rightStack to top of leftStack
					leftStack[left++] = rightStack[right-1];
					rightStack[right-1] = *buffer;
					
					leftStack[left] = END_OF_FILE;
					rightStack[right] = END_OF_FILE;
					
				}
				else if(*buffer == RPAR){
					
					while(rightStack[right - 1] != LPAR){
						
						//pop elements from right stack and put on left stack till LPAR found
						leftStack[left++] = rightStack[right - 1];
						leftStack[left] = END_OF_FILE;
						right--;
						
					}
					
					right--;
					rightStack[right] = '\0';
					
				}
				else{
					
					rightStack[right++] = *buffer;
					rightStack[right] = END_OF_FILE;
					
				}
				
			}
			
		}
		
		buffer++;
		
	}
	
	while(right > 0){
		
		leftStack[left] = rightStack[right - 1];
		left++;
		leftStack[left] = '\0';
		right--;
		rightStack[right] = '\0';
		
	}
	
	//copy leftStack -> buffer
	int i = left;
	
	while(i > 0){
		
		*startPtr = leftStack[i-1];
		*startPtr++;
		*startPtr = END_OF_FILE;
		i--;
		
	}
	
	/*
	while(i < left){
		
		*startPtr = leftStack[i];
		*startPtr++;
		*startPtr = END_OF_FILE;
		i++;
		
	}
	*/
	
	return startPtr;
	
	//printf("leftStack: %s\n", leftStack);
	//printf("rightStack: %s\n", rightStack);
	
}
