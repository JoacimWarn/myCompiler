#include <stdio.h>
#include <stdlib.h>

#define BUFFER 255

int str_cmp(char*, char*);

struct keywords{
	
	struct keywords* next;
	char* key;
	
};

struct keywords* addWord(struct keywords* temp, char* word){
	
	printf("%s", word);
	
	if(temp == NULL){
		
		temp = (struct keywords*) malloc(sizeof(struct keywords));
		temp->key = word;
		temp->next = NULL;
		
		printf("storing word:%s\n", word);
		
	}
	else if(!str_cmp(word, temp->key)){
		printf("ord finns redan");
		//keyword already exist skip
		return temp;
		
	}
	else{
		
		temp->next = addWord(temp->next, word);
		
	}
	
	return temp;
	
}

void printKeywords(struct keywords* temp){
	
	if(temp != NULL){
		
		printf("%s\n", temp->key);
		printKeywords(temp->next);
		
	}
	
}

char* readFile(char* buffer){
	
	char word;
	FILE* fp;
	fp = fopen("test.txt", "r");
	
	while((word = getc(fp)) != EOF){
		
		*buffer = word;
		*buffer++;
		
	}
	
	fclose(fp);
	return buffer;
	
}

int main(){
	
	int i, j, space;
	
	char keys[BUFFER];
	char word[BUFFER];
	
	struct keywords* root;
	root = NULL;
	
	readFile(keys);
	
	space = 0;
	
	for(i = 0; i < BUFFER; i++){
		
		//printf("%c", keys[i]);
		//word[i] = keys[i];
		
		if(keys[i] == '\n'){
			
			for(j = space; j < i; j++){
				
				word[j + space] = keys[j + space];
				
			}
			
			//root = addWord(root, word);
			space = i + 1;
			printf("%d\n", space);
			
		}
		
	}
	
	for(i = 0; i < BUFFER; i++) printf("%c", word[i]);
	
	//printf("%s", word);
	
	//printf("%s", keys);
	//root = addWord(root, keys);
	
	//root = readFile(root);
	//root = addWord(root, "lol");
	//root = addWord(root, "hej");
	
	
	
	//printKeywords(root);
	
	return 0;
	
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//return 0 if same word
int str_cmp(char* s, char* t){
	
	while(*s == *t){
		
		printf("\n%c %c", *s, *t);
		
		if(*s == '\0' && *t == '\0') return 0;
		
		*s++;
		*t++;
		
	}
	
	return 1;
	
}