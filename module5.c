#include "module8.h"
#include "module5.h"
#include "module6.h"

int isNumber5(char *str)
{
	int num = 0, i = 0;
	while(str[i] != '\0')
	{
		if(str[i] >= '0' || str[i] <= '9')
			num = atoi(str);
		else
			return 0;
		i++;	
	}
	return num;
}

int shlcheckerfunc(FILE *fp)
{
	FILE *error =fopen("error.txt", "w+");
	const char s[] = " \n\t";
	char *token, command = 'x', tempcommand[5], str[60];
	int lineno, preline, flag = 1, ctoken = 0, cline = 0, i = 0, ERROR = 0;
	for (int c = getc(fp); c != EOF; c = getc(fp))
	{
		if (c == '\n') // Increment ctoken if this character is newline
			cline = cline + 1; 
	}
	fseek(fp, 0, SEEK_SET);	
	while(flag <= cline)//Iteration for each line of SHL. 
	{
		fgets (str, 60, fp);
		token = strtok(str, s);
		
		while(token != NULL)
		{
			int len = strlen(token);
			if(ctoken == 0)// line number checking
			{
				char var1 = token[0];
			
				lineno = isNumber5(token);
				if(lineno == 0)//Non Numberic Line Numbering.
				{
					fprintf(error,"\n  ERROR @ %02d : Invalid choice of line number(Non-intger value).", flag);
					ERROR = 1;
				}
				if(lineno > 0)
				{
					if(flag == 1)
					{
						preline = lineno;
					}					
					else
					{
						if(lineno - 1 != preline)///Non Ascending Line Numbering.
						{
							fprintf(error,"\n  ERROR @ %02d : Invalid choice of line number (Invalid Order).", flag );
							ERROR = 1;								
						}
						preline = lineno;
					}
				}
				// Negative Line number.
				else if(lineno < 0)
				{
					fprintf(error,"  ERROR @ %02d : Invalid choice of line number(Negative Number).", flag);
					ERROR = 1;
				}								
				
			}		
			
			if(ctoken == 1)
			{
				if(len > 5)// length of command.
				{
					fprintf(error, "\n  ERROR @ %02d : Invalid SHL command.",flag);
					ERROR = 1;
				}			
				else
				{
					char tempcommand[len];
					strcpy(tempcommand, token);

					if(strcmp(tempcommand,"rem") == 0)
						command = 'r';
					else if(strcmp(tempcommand,"input") == 0)
						command = 'i';
					else if(strcmp(tempcommand,"let") == 0)
						command = 'l';
					else if(strcmp(tempcommand,"print") == 0)
						command = 'p';
					else if(strcmp(tempcommand,"goto") == 0)
						command = 'g';
					else if(strcmp(tempcommand,"end\n") == 0)
					{
						command = 'e';
						if(cline != flag)
						{
							ERROR = 1;
							fprintf(error, "\n  ERROR @ %02d : Statement after end encountered.",flag);
						}
					}
					else if(strcmp(tempcommand,	"if") == 0)
						command = 'j';
					else
					{
						ERROR = 1;
						fprintf(error, "\n  ERROR @ %02d :  Invalid SHL command.", flag);
					}																									
				}//end of else						
			}// end of if token == 1
			if(command == 'i' || command == 'p' || command == 'l' || command == 'g') //token exceed case
			{
					if(ctoken > 2)
					{
						ERROR = 1;
						fprintf(error,"\n  ERROR @ %02d : Invalid Syntax(Number of Token Exceeded).", flag);
					}				
			}
			if(ctoken > 1)
			{
				if(command == 'i' || command == 'p' )//input and print
				{	
					if(ctoken == 2)
					{
						int varlen = strlen(token);
						char var = token[0];
						if(varlen > 2 || var < 'a' || var > 'z')
						{
							ERROR = 1;
							fprintf(error,"\n  ERROR @ %02d : Invalid choice of variable.", flag);
						}
					}										
				}
				
				if(command == 'l')//let
				{		
					if(ctoken == 2)
					{
						char letexp[len];
						char *letExp = letexp;
						strcpy(letexp,token);
						for(i = 0; i < len; i++)
						{
							char ctemp = (char)letexp[i];
							if(ctemp >= 'A' && ctemp <= 'Z')
							{
								ERROR = 1;
								fprintf(error,"\n  ERROR @ %02d : Invalid choice of variable.", flag);
							}
						}
					}											
				}
						
				if(command == 'g') //goto
				{
					if(ctoken == 2)
					{
						int temp = isNumber5(token);
						if(temp <= 0)
						{
							ERROR = 1;
							fprintf(error,"\n  ERROR @ %d : Invalid choice of gotoline number.", flag);
						}
						else if(temp > cline)
						{
							ERROR = 1;
							fprintf(error,"\n  ERROR @ %d : Invalid choice of gotoline number.", flag);
						}
					}										
				}
			
				if(command == 'e') //end
				{
					ERROR = 1;
					fprintf(error,"\n  ERROR @ %d : Invalid Syntax.", flag);
				}
			
				if(command == 'j') //jump
				{
					if(ctoken > 4)
					{
						ERROR = 1;
						fprintf(error,"\n  ERROR @ %d : Invalid Syntax(Number of Token Exceeded).", flag);
					}
					char ifexp[len];
					strcpy(ifexp,token);
					if(ctoken == 2)
					{
						for( int i = 0; i < len; i++)
						{
							char ctemp = (char)ifexp[i];
							if(ctemp >= 'A' && ctemp <= 'Z')
							{
								ERROR = 1;
								fprintf(error,"\n  ERROR @ %d : Invalid choice of variable.", flag);
							} 								
						}
					}
					//Check goto in if statement.
					if(ctoken == 3)
					{
						if(strcmp(ifexp,"goto") != 0)
						{
							ERROR = 1;
							fprintf(error,"\n  ERROR @ %d : Invalid Syntax.(check 'goto' token.)", flag);
						}
					}
					if(ctoken == 4)
					{
						int temp = isNumber5(ifexp);
						if(temp <= 0)
						{
							ERROR = 1;
							fprintf(error,"\n ERROR @ %d : Invalid choice of gotoline number.", flag);
						}
						else if(temp > cline)
						{
							ERROR = 1;
							fprintf(error,"\n  ERROR @ %d : Invalid choice of gotoline number.", flag);
						}
					}								
				}																		
			}
			ctoken++; 
			token = strtok(NULL, s);	
		}// end of tokenising loop
		command = 'x';	//Reseting command
		flag++;
		ctoken = 0; //Reseting token
	}// end of loop iterate through each line	
	fprintf(error,"\n", flag);
	fclose(error);
	return ERROR;
}
