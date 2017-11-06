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
	FILE *error =fopen("error.txt", "w");
	//FILE *aexp = fopen("arthexp.txt","w");
	char str[60];
	const char s[2] = " ";
	char *token, command = 'x', tempcommand[5];

	/* get the first token */
	//token = strtok(str, s);

	int lineno, preline;
	int flag = 1, ctoken = 0, cline = 0, i = 0, b;
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

		//printf("%s ", str);
		
		//Tokenising.		
		token = strtok(str, s);
		//printf("%s ", token);
		//Iteration for each word of line.
		while(token != NULL)
		{
			//printf("enter while loop\n");
			//Line Number Error Checking.
			int len = strlen(token);
			if(ctoken == 0)
			{
				//++lineno;
				lineno = atoi(token);
				
				//Non Numberic Line Numbering.
				if(lineno == 0)
				{
					fprintf(error,"\nError: Line Number at %d:Non-intger values . ", flag);
					
				}
				
				//Non Ascending Line Numbering.
				if(lineno > 0)
				{
					if(flag == 1)
					{
						preline = lineno;
					}					
					else
					{
						if(lineno - 1 != preline)
						{
							//printf("preline %d line %d", preline, lineno);
							fprintf(error,"\nError: Line Number at %d: Invalid Order.", flag - 1);
						}
						preline = lineno;
					}
				}
				// Negative Line number.
				else
				{
					fprintf(error,"\nError: Line Number at %d: Negative Number.", flag);
				}				
			}		
			
			if(ctoken == 1)
			{
				//printf("\nctoken %d token %s", ctoken, token);
				int tkncpy = 0;
				
				// Checking invalid command from length of command.
				if(len > 5)
				{
					fprintf(error, "\nError: Invalid SHL command.");
				}			
				else
				{
					// Making a copy of token.
					char tempcommand[len];
					while( tkncpy <= len ) 
					{
						tempcommand[tkncpy] = token[tkncpy];
						tkncpy++;
   					}
   					printf("%s", tempcommand);
   					//Identifying the command.
					if(strcmp(tempcommand,"rem") == 0)
					{
						command = 'r';
					}
					else if(strcmp(tempcommand,"input") == 0)
					{
						command = 'i';
						//printf("command %c flag %d \n", command, flag);	
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
					else if(strcmp(tempcommand,"end\n") == 0)
					{
						command = 'e';
						if(cline != flag)
						{
							fprintf(error, "\nWarning: Statement after end encountered.");
						}
					}
					else if(strcmp(tempcommand,	"if") == 0)
					{
						command = 'j';
					}					
					else
					{
						fprintf(error, "\nInvalid command in line %d.", flag);
					}																									
				}					
					//printf("command %c flag %d \n", command, flag);		
			}
			
			if(ctoken > 1)
			{
				//printf("enter ctoken > 1\n ");
				if(command == 'i')
				{
					if(ctoken > 2)
					{
						//printf("enter more token in input\n ");
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Input statement.", flag);
					}
					
					/*
					 * 
					 * 
					 * 
					 * Enter Input Code Here.
					 * 
					 * 
					 * 
					 * 
					 * 
					 * 
					 */
					
				}
				
				if(command == 'l')
				{
					if(ctoken > 2)
					{
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Let statement.", flag);
					}
	
					/*
					 * 
					 * 
					 * 
					 * Enter Let Code Here.
					 * 
					 * 
					 * 
					 * 
					 * 
					 * 
					 */					
												
				}
				
				if(command == 'p')
				{
					if(ctoken > 2)
					{
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Print statement.", flag);
					}	
					if(ctoken == 2)
					{
						int varlen = strlen(token);
						if(varlen > 1)
						{
							fprintf(error,"\nError: Print Statement at %d: Invalid choice of variable.", flag);
						}
						
						if
					}
										
					/*
					 * 
					 * 
					 * 
					 * Enter Print Code Here.
					 * 
					 * 
					 * 
					 * 
					 * 
					 * 
					 */					
									
				}
			
				if(command == 'g')
				{
					if(ctoken > 2)
					{
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Goto statement.", flag);
					}
					if(ctoken == 2)
					{
						int temp = atoi(token);
						//printf("Temp %d token %s", temp, token);
						if(temp <= 0)
						{
							fprintf(error,"\nError: Goto Statement at %d: Invalid line number ", flag);
						}
					}										
				}
			
				if(command == 'e')
				{
					fprintf(error,"\nError: End Statement at %d: Invalid Syntax for end statement. ", flag);
				}
			
				if(command == 'j')
				{
					if(ctoken > 4)
					{
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of If..goto statement.", flag);
					}
					char ifexp[len];
					int tkncpy = 0;
					while( tkncpy <= len ) 
					{
						ifexp[tkncpy] = token[tkncpy];
						tkncpy++;
					}	
					
					//Checks logical exp.				
					if(ctoken == 2)
					{
   						if(ifexp[0] < 'a' || ifexp[0] > 'z')
   						{
   							fprintf(error,"\nError: If Statement at %d: Invalid choice of variable'%c'.", flag, ifexp[0]);
   						}
   						
   						if(ifexp[3] < 'a' || ifexp[3] > 'z')
   						{
   							fprintf(error,"\nError: If Statement at %d: Invalid choice of variable'%c'.", flag, ifexp[3]);
   						}
						//printf("%c\n", ifexp[0]);
					}
					
					//Check goto in if statement.
					if(ctoken == 3)
					{
						if(strcmp(ifexp,"goto") != 0)
						{
							fprintf(error,"\nError: If Statement at %d: Invalid Syntax check 'goto' token.", flag);
						}
					}
					
					//Checks gotos line no..
					if(ctoken == 4)
					{
						int temp = atoi(ifexp);
						//printf("Temp %d", temp);
						if(temp <= 0)
						{
							fprintf(error,"\nError: If Statement at %d: goto line number invalid.", flag);
						}
					}
										
				}																			
			}

			ctoken++; //
			token = strtok(NULL, s);	
		}
		command = 'x';	//Reseting command to x
		flag++;
		ctoken = 0; //Reseting token count for next line of code. 
	}
	
	return 0;
}
