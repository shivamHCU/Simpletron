
#include <stdio.h>
#include "module8.h"
#include "module7.h"

#define SIZE 50

int stack7[SIZE];

int TOP7 = -1;

int smlInstructionCounter = 0; 
int smlInstruction[50]={0};

void push7(int data)
{
	if(TOP7 == SIZE - 1)
		printf("Overflow\n");
	else
		stack7[++TOP7] = data;

}

int pop7()
{
	int deleted;
	if(TOP7 == -1)
		printf("Underflow\n");
	else
		deleted = stack7[TOP7--]; 

	return deleted;
}

void showStack()
{
	int top7 = TOP7;
	while(top7!=-1)
		printf("Stack: %d\n", stack7[top7--]);
}


// Converts postfix expression to SML
int* convertToSML(char * postfixString)
{
	
	smlInstructionCounter = 0; 
	for(int i = 0 ; i < 50 ; i++)
		smlInstruction[i]= 0;
	//tokenizes the postfix expression and stores it in a string array
	char *expression[50];
	char *token = strtok(postfixString, " ");
	int counter = 0;
	while(token!=NULL)
	{
		expression[counter++] = token;
		token = strtok(NULL, " ");
	}


	int location;
	int operand1, operand2;
	char * finalOperator = expression[1];

	for(int i=2;i<counter;i++)
	{
		int opcode = 0;


		//If the expression contains a variable name, search for its location in symbol table and push it on the stack
		if(expression[i][0] >= 'a' && expression[i][0] <= 'z')
		{
			location = lookInToSymboltable(expression[i][0], 'V');
			push7(location);

		}

		//If the expression contains a constant, search for its location in symbol table(if not add it in the table) and push it on the stack
		else if(expression[i][0] >= '0' && expression[i][0] <='9')
		{
			int constant = atoi(expression[i]);
			location = lookInToSymboltable(constant, 'C');
			if(location == 00)
			{
				mainMemory[variableMemoryCounter] = constant;    // * added by shivam 
				addToSymbolTable(constant, 'C', variableMemoryCounter);
			}
			push7(variableMemoryCounter);
			variableMemoryCounter--;
		}

		//If the expression contains an operator, pop two elements and assign the opcode
		else if(expression[i][0] == '+' || expression[i][0] == '-' || expression[i][0] == '*' || expression[i][0] == '/')
		{

			operand2 = pop7();
			operand1 = pop7();

			switch(expression[i][0])
			{
				case '+': { opcode = 3000; break;}
				case '-': { opcode = 3100; break;}
				case '/': { opcode = 3200; break;}
				case '*': { opcode = 3300; break;}
			}
		}

		//if the expression contains more than 1 elements
		if(opcode != 0)
		{
			smlInstruction[smlInstructionCounter++] = 2000 + operand1;		//load instruction
			smlInstruction[smlInstructionCounter++] = opcode + operand2;	//operate instruction


			//looks if the temporary memory assigned after computation can be reused 
			int tempAddress1 = searchSymbolTable(operand1);
			int tempAddress2 = searchSymbolTable(operand2);
			int addressValue;

			if( tempAddress1 == 0 || tempAddress2 == 0)
			{
				if(tempAddress1 == 0 && tempAddress2 == 0)
				{
					addressValue = operand1>operand2?operand1:operand2;
				}
				else
				{
					if(tempAddress1 == 0)
						addressValue = operand1;
					else
						addressValue = operand2;
				}
			}
			else
			{
				addressValue = variableMemoryCounter;
				variableMemoryCounter--;
			}
			smlInstruction[smlInstructionCounter++] = 2100 + (addressValue);
			push7(addressValue);
		}

		else if(counter == 1)
		{
			operand1 = pop7();
			smlInstruction[smlInstructionCounter++] = 2000 + operand1;
		}
	}

	operand2 = pop7();
	
	//if(expression[0][0] >= 'a' && expression[0][0] <= 'z')
	//	{
	operand1 = lookInToSymboltable(expression[0][0], 'V');		
	//	}
	//else
	//	printf("Invalid\n");

	smlInstruction[smlInstructionCounter++] = 2000 + operand1;
	smlInstruction[smlInstructionCounter++] = 3100 + operand2;
	switch(finalOperator[0])
	{
		case '=': 
				{
					if(finalOperator[1] == '=')
					{
						smlInstruction[smlInstructionCounter++] = 4200;
					}
					else
					{
						--smlInstructionCounter;
						--smlInstructionCounter;
						smlInstruction[smlInstructionCounter++] = 2000 + operand2;
						smlInstruction[smlInstructionCounter++] = 2100 + operand1;
					}
					break;
				}
		case '<':
				{
					if(finalOperator[1] == '=')
					{

						smlInstruction[smlInstructionCounter++] = 4200;
						smlInstruction[smlInstructionCounter++] = 4100;
					}
					else
					{
						smlInstruction[smlInstructionCounter++] = 4100;
					}
					break;


				}
		case '>':
				{
					--smlInstructionCounter;
					--smlInstructionCounter;
					smlInstruction[smlInstructionCounter++] = 2000 + operand2;
					smlInstruction[smlInstructionCounter++] = 3100 + operand1;
					if(finalOperator[1] == '=')
					{

						smlInstruction[smlInstructionCounter++] = 4200;
						smlInstruction[smlInstructionCounter++] = 4100;
					}
					else
					{
						smlInstruction[smlInstructionCounter++] = 4100;
					}
					break;

				}
		case '!':
				{
					if(finalOperator[1] == '=')
					{

						smlInstruction[smlInstructionCounter++] = 4200;
						smlInstruction[smlInstructionCounter++] = 4000;
					}
					break;
				}
	}
	
	//returns the final SML instructions
	return smlInstruction;	
}

