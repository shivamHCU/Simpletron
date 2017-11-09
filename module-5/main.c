/*
 * cline: represent count of line in SHL code file.
 * ctoken: represents count of token in each line.
 * flag: to iterate through each line of SHL file.
 * lineno: to iterate, maintain and validate line no of SHL file.
 * a: contains the line numbers.
 * str: contains each line of SHL code.
 * tkncpy: used to cpy the same case command.
 */

#include <string.h>
#include<stdlib.h>
#include <stdio.h>
#include<ctype.h>

int shlcheckerfunc(FILE *fp, FILE *error);

int main () 
{
	FILE *fp = fopen("test.txt", "r");
	FILE *error =fopen("error.txt", "w");
	//FILE *aexp = fopen("arthexp.txt","w");
	//FILE *aexp = fopen("arthexp.txt","w");
	int e = shlcheckerfunc(fp, error);
	printf("\n Error%d \n", e);
	
	fclose(fp);
	fclose(error);
	
	return 0;
}
