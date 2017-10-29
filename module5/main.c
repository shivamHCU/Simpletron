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

int main () 
{
	FILE *fp = fopen("test.txt", "r");
	FILE *error =fopen("error.txt", "a+");
	//FILE *aexp = fopen("arthexp.txt","w");
	char str[60];
	const char s[2] = " ";
	char *token, command = 'x', tempcommand[5];

	/* get the first token */
	//token = strtok(str, s);


	int flag = 1, ctoken = 0, cline = 0, i = 0, b, lineno = -1;
	for (int c = getc(fp); c != EOF; c = getc(fp))
	{
		if (c == '\n') // Increment ctoken if this character is newline
		cline = cline + 1; 
	}
	//printf("%d", cline);
	int a[cline];
	fseek(fp, 0, SEEK_SET);
	
	//Iteration for each line of SHL.   	
	while(flag <= cline)
	{
		fgets (str, 60, fp);
		
		//Removing Black Spaces in SHL code.

		
		//Tokenising.		
		token = strtok(str, s);
		
		//Iteration for each word of line.
		while(token != NULL)
		{
			
			//Line Number Error Checking.
			if(ctoken == 0)
			{
				++lineno;
				a[lineno] = atoi(token);
				
				//Non Numberic Line Numbering.
				if(a[lineno] == 0)
				{
					fprintf(error,"Error: Line Number at %d:Invalid format to number line use only intger values . \n", cline);
				}
				
				//Non Ascending Line Numbering.
				if(lineno > 0)
				{
					if(a[lineno - 1] > a[lineno])
					{
						fprintf(error,"Error: Line Number at %d: Invalid Order.", cline - 1);
					}
				}				
			}		
			
			if(ctoken == 1)
			{
				//printf("\nctoken %d token %s", ctoken, token);
				int len = strlen(token), tkncpy = 0;
				
				// Checking invalid command from length of command.
				if(len > 5)
				{
					fprintf(error, "\nError: Invalid SHL command.\n");
				}			
				else
				{
					// Making command of same case.
					char tempcommand[len];
					while( tkncpy <= len ) 
					{
						tempcommand[tkncpy] = tolower(token[tkncpy]);
						tkncpy++;
   					}
   					
   					//Identifying the command.
					if(strcmp(tempcommand,"rem") == 0)
					{
						command = 'r';
					}
					else if(strcmp(tempcommand,"input") == 0)
					{
						command = 'i';
					}
					else if(strcmp(tempcommand,"let") == 0)
					{
						command = 'l';
					}
					else if(strcmp(tempcommand,"print") == 0)
					{
						command = 'p';
					}
					else if(strcmp(tempcommand,"goto") == 0)
					{
						command = 'g';
					}					
					else if(strcmp(tempcommand,"end") == 0)
					{
						command = 'e';
					}
					else if(strcmp(tempcommand,	"if") == 0)
					{
						command = 'j';
					}					
					else
					{
						fprintf(error, "\nInvalid command in line %d\n", flag);
					}																									
				}					
				
			}
			ctoken++; //
			token = strtok(NULL, s);
			
		}
		printf("command %c flag %d \n", command, flag);	
		command = 'x';	//Reseting command to x
		flag++;
		ctoken = 0; //Reseting token count for next line of code. 
	}
	
	for(int i = 0; i < cline; ++i)
		printf("%d ", a[i]);		
	return(0);
}
