#include <stdio.h>
#include <stdlib.h>

#define BUFFER 255

int str_cmp(char*, char*);

struct keywords{
	
	struct keywords* next;
	char* key;
	
};

struct keywords* addWord(struct keywords* temp, char* word){
	
	if(temp == NULL){
		
		temp = (struct keywords*) malloc(sizeof(struct keywords));
		temp->key = word;
		temp->next = NULL;
		
	}
	else if(!str_cmp(word, temp->key)){
		
		//keyword already exist skip
		return temp;
		
	}
	else{
		
		temp->next = addWord(temp->next, word);
		
	}
	
	return temp;
	
}

struct keywords* readFile(struct keywords* temp){
	
	int i;
	char word;
	FILE* fp;
	fp = fopen("test.txt", "r");
	i = 0;
	
	while((word = getc(fp)) != EOF){
		
		
		if(word == '\n' || word == ' '){
			
			
		}
		
	}
	
	fclose(fp);
	
}

int main(){
	
	struct keywords* root;
	root = NULL;
	
	root = readFile(root);
	
	//printf("%s", root->key);
	
	return 0;
	
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//return 0 if same word
int str_cmp(char* s, char* t){
	
	while(*s++ == *t++){
		
		if(*s == '\0' && *t == '\0' || (*s == '\n' && *t == '\n')) return 0;
		
	}
	
	return 1;
	
}