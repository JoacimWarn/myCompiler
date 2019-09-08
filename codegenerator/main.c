#include <stdio.h>
#include <stdlib.h>

void gen(FILE* fpOut){
	
	
	
}

int main(){
	
	FILE* fpWrite = NULL;
	
	int eaxReg, ebxReg;
	
	/*
	__asm__("mov $0x5, %%eax":"=a"(eaxReg));
	
	asm("mov $0x2, %ebx;"
		"sub $0x1, $0x2, %ebx"
	);
	
	asm("mov %%ebx,%%ebx":"=b"(ebxReg));
	//asm("mov ":(ebxReg)"%ebx");
	
	printf("eax:%d\nebx:%d\n", eaxReg, ebxReg);
	
	
	asm(
		"mov $0x0, %eax;"
		"L1:"
		""
		"inc %eax;"
		"cmp $0xA, %eax;"
		"JL L1"
	);
	
	asm("mov %%eax,%%eax":"=a"(eaxReg));
	
	printf("eax:%d", eaxReg);
	*/
	
	asm(
		"mov $0x3, %ebx;"
		"sub $0x1, %ebx;"
		"div $0x2, %ebx"
	);
	
	printf("\nPress any key to continue...");
	getch();
	
	return 0;
	
}

