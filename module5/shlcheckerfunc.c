#include <string.h>
#include<stdlib.h>
#include <stdio.h>
#include<ctype.h>

int shlcheckerfunc(FILE *fp, FILE *error)
{
	char str[60];
	const char s[2] = " ";
	char *token, command = 'x', tempcommand[5];

	/* get the first token */
	//token = strtok(str, s);

	int lineno, preline, flag = 1, ctoken = 0, cline = 0, i = 0, b, ERROR = 0;
	for (int c = getc(fp); c != EOF; c = getc(fp))
	{
		if (c == '\n') // Increment ctoken if this character is newline
			cline = cline + 1; 
	}
	
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
				char var1 = token[0];
				if(var1 == '\n')
				{
					fprintf(error, "\nWarning: Newline Line with no commands at %d.", flag);
					ERROR = 1;
				}
				else
				{
					lineno = atoi(token);
			
			
					//Non Numberic Line Numbering.
					if(lineno == 0)
					{
						fprintf(error,"\nError: Line Number at %d:Non-intger values . ", flag);
						ERROR = 1;
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
								ERROR = 1;								
							}
							preline = lineno;
						}
					}
					// Negative Line number.
					else
					{
						fprintf(error,"\nError: Line Number at %d: Negative Number.", flag);
						ERROR = 1;
					}									
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
					ERROR = 1;
				}			
				else
				{
					// Making a copy of token.
					char tempcommand[len];
					strcpy(tempcommand, token);
   					//printf("%s", tempcommand);
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
							ERROR = 1;
							fprintf(error, "\nWarning: Statement after end encountered.");
						}
					}
					else if(strcmp(tempcommand,	"if") == 0)
					{
						command = 'j';
					}					
					else
					{
						ERROR = 1;
						fprintf(error, "\nInvalid command in line %d.", flag);
					}																									
				}					
					//printf("command %c flag %d \n", command, flag);		
			}
			
			if(ctoken > 1)
			{
				//printf("enter ctoken > 1\n ");
				if(command == 'i' || command == 'p')
				{
					if(ctoken > 2)
					{
						
						if(command == 'i')
						{
							ERROR = 1;
							fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Input statement.", flag);
						}		
						if(command == 'p')
						{
							ERROR = 1;
							fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Print statement.", flag);
						}
						//printf("enter more token in input\n ");
						
					}
					if(ctoken == 2)
					{
						int varlen = strlen(token);
						char var = token[0];
						printf("%c", var);
						if(varlen > 2)
						{
							ERROR = 1;
							fprintf(error,"\nError: At %d: Invalid choice of variable.", flag);
						}
						
						if(var < 'a' || var > 'z')
						{
							ERROR = 1;
							fprintf(error,"\nError: At %d: Invalid choice of variable.", flag);
						}
					}										
				}
				
				if(command == 'l')
				{
					if(ctoken > 2)
					{
						ERROR = 1;
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Let statement.", flag);
					}
					
					if(ctoken == 2)
					{
						char letexp[len];
						strcpy(letexp,token);
						for(i = 0; i < len; i++)
						{
							char ctemp = (char)letexp[i];
							if(ctemp >= 'A' && ctemp <= 'Z')
							{
								ERROR = 1;
								fprintf(error,"\nError: Let statement at %d: Invalid variable used.", flag);
							}
						}
						
						/*
						 * 
						 * module 6 function.
						 * 
						 */
					}												
				}
						
				if(command == 'g')
				{
					if(ctoken > 2)
					{
						ERROR = 1;
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of Goto statement.", flag);
					}
					if(ctoken == 2)
					{
						int temp = atoi(token);
						//printf("Temp %d token %s", temp, token);
						if(temp <= 0)
						{
							ERROR = 1;
							fprintf(error,"\nError: Goto Statement at %d: Invalid line number ", flag);
						}
					}										
				}
			
				if(command == 'e')
				{
					ERROR = 1;
					fprintf(error,"\nError: End Statement at %d: Invalid Syntax for end statement. ", flag);
				}
			
				if(command == 'j')
				{
					if(ctoken > 4)
					{
						ERROR = 1;
						fprintf(error,"\nError: Tokens Exceeded at %d: Invalid Syntax of If..goto statement.", flag);
					}
					char ifexp[len];
					strcpy(ifexp,token);
					//Checks logical exp.				
					if(ctoken == 2)
					{
						for( int i = 0; i < len; i++)
						{
							char ctemp = (char)ifexp[i];
							if(ctemp >= 'A' && ctemp <= 'Z')
							{
								ERROR = 1;
								fprintf(error,"\nError: If statement at %d: Invalid variable used.", flag);
							} 								
						}
						
					
						//printf("%c\n", ifexp[0]);
						/*
						 * 
						 * module 6 function.
						 * 
						 * 
						 */
					}
					
					//Check goto in if statement.
					if(ctoken == 3)
					{
						if(strcmp(ifexp,"goto") != 0)
						{
							ERROR = 1;
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
							ERROR = 1;
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
	return ERROR;
}
