#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define BUFFER 512

#define is_digit(c) ('0' <= c && c <= '9')
#define ushort unsigned short int

char* infixToPostfixReverse(char*);
char* buildExpression(char*);

struct tree{
	
	struct tree* left;
	struct tree* right;
	
	
	
	struct expression* exp;
	
};

struct statement{
	
	struct expression* condition;
	char* body;
	
};

struct expression{
	
	struct expression* left;
	struct expression* right;
	char type;		/* D or P or I */
	int value;		/* for D */
	char operator;	/* for P */
	char operands;	/* for P if already has two operands */
	
};

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
	/*
	if(temp->type == 'P'){
		
		if(temp->right != 0 && temp->left != 0){
			
			if(temp->right->type == 'D' && temp->left->type == 'D'){
				
				temp->operands = '1';
				
			}
			else if((temp->right->type == 'D' || temp->right->type == 'P') && (temp->left != 0)){
				
				temp->operands = '1';
				
			}
			
		}
		
	}
	*/
	
}

void printBottomUp(struct expression* temp){
	
	if(temp == NULL) return;
	
	printBottomUp(temp->right);
	
	printBottomUp(temp->left);
	
	printf("op:%c val:%c type:%c\n", temp->operator, temp->value, temp->type);
	
}

struct expression* addNewElement(struct expression* temp, char data){
	
	int static nrOfElements = 0;
	
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
		
		nrOfElements++;
		
	}
	else{
		
		if(!isalnum(data) && !isdigit(data)){
			//operator
			if(temp->right == 0) temp->right = addNewElement(temp->right, data);
			else{
				
				if(temp->right->type == 'D' && temp->left == 0){
					printf("going left:%c\n", data);
					temp->left = addNewElement(temp->left, data);
					
				}
				else if(temp->right->type == 'D' && temp->left != 0){
					
					if(temp->left->type == 'P' && temp->left->operands == '0'){
						printf("going left:%c\n", data);
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
					printf("left:%c\n", data);
					temp->left = addNewElement(temp->left, data);
					
				}
				else if(temp->right->type == 'P' && temp->right->operands == '0'){
					
					temp->right = addNewElement(temp->right, data);
					
				}
				else if(temp->right->type == 'P' && temp->right->operands == '1'){
					printf("left:%c\n", data);
					temp->left = addNewElement(temp->left, data);
					
				}
				
				//temp->right = addNewElement(temp->right, data);
				
			}
			else if(temp->type == 'P' && temp->right == 0){
				printf("right:%c\n", data);
				//right node is empty, allocate it
				temp->right = addNewElement(temp->right, data);
				
			}
			
		}
		
	}
	/*
	else{
		
		//expression tree is not empty, look for empty space
		//if it is a operator then traverse right till you find null space then allocate
		if(!isalnum(data) && !isdigit(data)) temp->right = addNewElement(temp->right, data);		//operator
		else{
			
			//digit or identifier
			if(temp->type == 'P' && temp->right != 0){
				
				if(temp->right->type == 'P' && temp->right->operands == '1'){
					
					if(temp->left == 0){
						
						temp->left = addNewElement(temp->left, data);
						
					}
					
				}
				else if(temp->right->type == 'P'){
					
					printf("right:%c\n", data);
					temp->right = addNewElement(temp->right, data);
					
				}
				else if(temp->right->type == 'D'){
					
					if(temp->left == NULL){
						
						printf("left:%c\n", data);
						temp->left = addNewElement(temp->left, data);
						
					}
					else if(temp->right != 0 && temp->left != 0){
						
						//reach bottom of the tree, need to traverse again
						printf("hej123\n");
						
					}
					
				}
				
			}
			else if(temp->type == 'P' && temp->right == 0){
				
				printf("right:%c\n", data);
				temp->right = addNewElement(temp->right, data);
				
			}
			else if(temp->type == 'P' && temp->left == 0){
				
				printf("left:%c\n", data);
				temp->left = addNewElement(temp->left, data);
				
			}
			
		}
		
	}
	*/
	
	return temp;
	
}

int main(){
	
	struct tree* program = NULL;
	
	/*
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
	
	printBottomUp(root);
	
	
	
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
	
	printBottomUp(test);
	*/
	
	//char* a = "a = a + 2 / (3-1)\0";
	//char* theExpression;
	//theExpression = buildExpression(a);
	//printf("%s", theExpression);
	//evaluateExpression(expression);
	//root->exprPtr = buildExpression(root->exprPtr, a);
	
	
	
	FILE* fpRead;
	FILE* fpWrite;
	int ch, i;
	char buffer[BUFFER];
	
	i = 0;
	
	fpRead = fopen("outputLexer.txt", "r");
	
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
	
	while((ch = fgetc(fpRead)) != EOF){
		
		//printf("%c", ch);
		
		//if(buffer[0] == IDENTIFIER);
		
		if(ch == SEMI_COLON){
			
			buffer[i] = END_OF_FILE;
			i = 0;
			
			//printf("buffer:\n%s", buffer);
			
		}
		
		buffer[i++] = ch;
		
	}
	
	fclose(fpRead);
	//fclose(fpWrite);
	
	return 0;
	
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

char* buildExpression(char* buffer){
	
	char* startPtr = buffer;
	
	//a=a+2/(3-1)\0
	ushort size = 50;
	ushort i = 0;
	//char buf[size];
	char buf[size];
	
	while(*buffer){
		
		//copy contents of buffer in to buf, and remove all white spaces
		
		if(!isspace(*buffer)){
			
			buf[i] = *buffer;
			i++;
			buf[i] = END_OF_FILE;
			
		}
		
		*buffer++;
		
	}
	
	infixToPostfixReverse(buf);
	
	//printf("%s", buf);
	
	int j = 0;
	
	
	//build a tree from the expression
	struct expression* test = (struct expression*) malloc(sizeof(struct expression));
	i = 0;
	int level = 1;
	
	while(buf[i] != END_OF_FILE){
		
		if(buf[i] == PLUS || buf[i] == MINUS || buf[i] == TIMES || buf[i] == DIV || buf[i] == ASSIGN){
			//printf("%c", buf[i]);
			//operator
			if(i == 0){
				
				test->operator = buf[i];
				test->type = 'P';
				
			}
			else if(i > 0){
				
				if(test->right->operator != ASSIGN && test->right->operator != TIMES && test->right->operator != DIV && test->right->operator != MINUS && test->right->operator != PLUS){
					
					test->right = (struct expression*) malloc(sizeof(struct expression));
					test->right->operator = buf[i];
					test->right->type = 'P';
					level = 2;
					
				}
				else if(test->right->right->operator != ASSIGN && test->right->right->operator != TIMES && test->right->right->operator != DIV && test->right->right->operator != MINUS && test->right->right->operator != PLUS){
					//printf("%c", buf[i]);
					test->right->right = (struct expression*) malloc(sizeof(struct expression));
					test->right->right->operator = buf[i];
					test->right->right->type = 'P';
					level = 3;
					
				}
				else{
					//printf("%c", buf[i]);
					test->right->right->right = (struct expression*) malloc(sizeof(struct expression));
					test->right->right->right->operator = buf[i];
					test->right->right->right->type = 'P';
					level = 4;
					
				}
				
			}
			
		}
		else if(isalnum(buf[i])){
			
			int static fullLevel = 0;
			
			//decimal or identifier
			//add on the current level
			if(level == 4 && fullLevel != 4){
				
				if(!isdigit(test->right->right->right->right->value)){
					
					test->right->right->right->right->value = buf[i];
					test->right->right->right->right->type = 'D';
					
				}
				else if( !isdigit(test->right->right->right->left->value) ){
					
					test->right->right->right->left = (struct expression*) malloc(sizeof(struct expression));
					test->right->right->right->left->value = buf[i];
					test->right->right->right->left->type = 'D';
					fullLevel = 4;
					
					
					test->right->right->right->right->right->type = END_OF_FILE;
					test->right->right->right->right->left->type = END_OF_FILE;
					
				}
				
			}
			else if(fullLevel == 4 && isdigit(buf[i])){
				
				test->right->right->left = (struct expression*) malloc(sizeof(struct expression));
				test->right->right->left->value = buf[i];
				test->right->right->left->type = 'D';
				
				fullLevel = 3;
				
				test->right->right->left->right->type = END_OF_FILE;
				test->right->right->left->left->type = END_OF_FILE;
				
			}
			else if(fullLevel == 3){
				
				test->right->left = (struct expression*) malloc(sizeof(struct expression));
				test->right->left->value = buf[i];
				test->right->left->type = 'D';
				
				fullLevel = 2;
				
				test->right->left->left->type = END_OF_FILE;
				test->right->left->right->type = END_OF_FILE;
				
			}
			else if(fullLevel == 2){
				
				test->left = (struct expression*) malloc(sizeof(struct expression));
				test->left->value = buf[i];
				test->left->type = 'D';
				
				test->left->left->type = END_OF_FILE;
				test->left->right->type = END_OF_FILE;
				
			}
			
		}
		
		i++;
		
	}
	
	//printTestTree(test);
	
	return buffer;
	
}