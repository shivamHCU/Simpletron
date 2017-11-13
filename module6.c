#include "module6.h"
#include "module8.h"

int top = -1 ; 

int stack[50];
int isNumber(char c)
{
    if(c >= '0' && c <= '9')
    return 1;
    else
    return 0;
}

int isAlfNum(char c)
{   
    int flag = 0;
    if(c >= 'a' && c <= 'z')
    {
        flag = lookInToSymboltable((int)c,'V');
        if (flag != 0)
            return 1;
        else    
            return 0;
    }
    else
        return 0;
}

int isOperator(char c)
{
    if(c == '+' || c == '-' || c == '/' || c == '*' || c == '>' || c == '<' || c == '=')
        return 1;
    else 
        return 0; 
}

int isOperator1(char c)
{
    if(c == '<' || c == '>' || c == '!' || c == '=')
        return 1;
    else
        return 0;
}


int validateInfix(char *str1)
{

  int i=0,l=0,j=0,k=0;
    char str[100];
    while(str1[i] != '\0')
    {
        if(str1[i] == ' ')
        {
            return 1;
        
        }
        else
        {
            if(str1[i] == '(')
                push(str1[i]);
            else if(str1[i] == ')')
                pop();
            else
            {
                str[k++]=str1[i];
            }
        }    
        i++;
    }
    str[k]='\0';
    i=0;
    int len=strlen(str);

        if(top == -1)
    {
     while(strlen(str) >= i+2)
     {
        if(isAlfNum(str[i]) && isOperator(str[i+1]) && (isAlfNum(str[i+2]) ))
        {
            i=i+2;
        }   
        else if(isAlfNum(str[i]) && isOperator1(str[i+1]) && (str[i+2] == '=') && isAlfNum(str[i+3]))
        {
            i=i+3;
        }
        else if(isAlfNum(str[i]) && isOperator(str[i+1]) && (isAlfNum(str[i+2]) || isNumber(str[i+2])))
        {
            i=i+2;
                }
        else if(isAlfNum(str[i]) && isOperator1(str[i+1]) && str[i+2] == '=' && (isAlfNum(str[i+3]) || isNumber(str[i+3])))
        {
            i=i+3;
        }
        else if(isNumber(str[i]))
        {
            while(str[i+1] !=  (isOperator(str[i+1]) || isOperator1(str[i+1])))
            {
            i++;
            }
            i=i+1;
            if(isOperator(str[i]) && (isAlfNum(str[i+1]) || isNumber(str[i+1])))
                {
                 i=i+1;
            }
            else if((isOperator1(str[i]) && str[i+1]=='=') && (isAlfNum(str[i+2]) || isNumber(str[i+2])))
            {
            i=i+2;                                
            }
            else if(isOperator(str[len-1]))
            {
            //printf("invalid operator is inserted\n");
            return 1;
            }
            else if(isOperator1(str[len-2]) && str[len-1]=='=')
            {
            return 1;//invalid operator is inserted
           }
        }
        else
        {
            
            return 1;//invalid infix expression
        }



    }
    //printf("valid expression\n");
    return 0;
     }
     else
        // printf("invalid Parenthesis is inserted\n");
return 0;
}

 
char* convertToPostfix(char *infix_expression)
{
      unsigned int count, temp = 0;
      char next;
      char character; 
      int len = strlen(infix_expression);
      char *postfix_expression = malloc(2 * len * sizeof(char));
      for(int i = 0; i < len ; i++)
      {
            character = infix_expression[i];
                  switch(character)
                  {
                        case '(': push(character);
                                  break;
                        case ')':
                                  while((next = pop()) != '(')
                                  {
                                        postfix_expression[temp++] = next;
                                        postfix_expression[temp++] = ' ';
                                  }
                                  break;
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                                  while(!isEmpty() && priority(stack[top]) >= priority(character))
                                  {
                                    postfix_expression[temp++] = pop();
                                    postfix_expression[temp++] = ' ';   
                                  }
                                  push(character);
                                  break;
                        default: 
                                  postfix_expression[temp++] = character;
                                  while(isNumber(infix_expression[i+1]))
                                  {      
                                    i++;  
                                    postfix_expression[temp++] = infix_expression[i];
                                  }
                                  if(infix_expression[i+1] != '=' || i == 0)
                                    postfix_expression[temp++] = ' ';
                  }
      }
      while(!isEmpty()) 
      {
      		postfix_expression[temp++] = pop();
            postfix_expression[temp++] = ' ';
      }
      postfix_expression[temp] = '\0';

 return postfix_expression;     
}
 
int priority(char character)
{
      switch(character)
      {
            case '(': return 0;
            case '+':
            case '-':
                      return 1;
            case '*':
            case '/':
            case '%':
                      return 2;
            default:
                      return 0;
      }
}
 
void push(int character)
{
      if(top > 50)
      {
            printf("Stack Overflow\n");
            exit(1);
      }
      top = top + 1;
      stack[top] = character;
}
 
int check_space_tabs(char character)
{
      if(character == ' ' || character == '\t')
      {
            return 1;
      }
      else
      {
            return 0;
      }
}

int pop()
{
      if(isEmpty())
      {
            printf("Stack is Empty\n");
            exit(1);
      }
      return(stack[top--]);
}
 
int isEmpty()
{
      if(top == -1)
      {
            return 1;
      }
      else
      {
            return 0;
      }
}