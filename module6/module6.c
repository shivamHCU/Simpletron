#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char stack[100];

int top = -1;

int isnumber(char c)
{
    if(c >= '0' && c <= '9')
	return 1;
    else
	return 0;
}

void push(char data)
{
    if(top>100)
    {
	printf("Stack is full\n");
    }
    else
    {
	stack[++top] = data;
    }
}

char pop1()
{
	return stack[top--];
}

void pop()
{    
	stack[top--]=0;   
}
int isalnum(char c)
{
	if(c >= 'a' && c <= 'z' )
	{
		return 1;
	}
	else
		return 0;
}

int isoperator(char c)
{
	if(c == '+' || c == '-' || c == '/' || c == '*' || c == '>' || c == '<')
		return 1;
	else 
		return 0; 
}

int isoperator1(char c)
{
    if(c == '<' || c == '>' || c == '!' || c == '=')
		return 1;
    else
		return 0;
}

int precedence2(char c)
{
    if(c == '>' || c == '<')
	return 2;
    else if(c == '!' || c == '=')
	return 1;
    else
	return 0;
}

int precedence(char c)
{
	if(c=='*'|| c=='/')
	return 4;
	else if( c=='+'|| c=='-')
	return 3;
	else if(c=='>' || c=='<')
	return 2;
	else if(c=='!' || c=='=')
	return 1;
	else
	return 0;
	
}


int validateInfix(char str1[])
{
	int i=0,l=0,j=0,k=0;
	char str[100];
	while(str1[i] != '\0')
	{
		if(str1[i] == ' ')
		{
			printf("space is not allowed\n");
			return 0;
		}
		i++;
	}
	i=0;
	while(str1[i] != '\0')
	{
	    if(str1[i] == '(')
		push(str1[i]);
	    else if(str1[i] == ')')
		pop();
	    else
	    {
		str[k++]=str1[i];
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
		if(isalnum(str[i]) && isoperator(str[i+1]) && (isalnum(str[i+2]) ))
		{
			i=i+2;
		}	
		else if(isalnum(str[i]) && isoperator1(str[i+1]) && (str[i+2] == '=') && isalnum(str[i+3]))
		{
			i=i+3;
		}
		else if(isalnum(str[i]) && isoperator(str[i+1]) && (isalnum(str[i+2]) || isnumber(str[i+2])))
		{
			i=i+2;
                }
		else if(isalnum(str[i]) && isoperator1(str[i+1]) && str[i+2] == '=' && (isalnum(str[i+3]) || isnumber(str[i+3])))
		{
		    i=i+3;
		}
		else if(isnumber(str[i]))
		{
		    while(str[i+1] !=  (isoperator(str[i+1]) || isoperator1(str[i+1])))
		    {
			i++;
		    }
		    i=i+1;
		    if(isoperator(str[i]) && (isalnum(str[i+1]) || isnumber(str[i+1])))
	            {
			     i=i+1;
		    }
		    else if((isoperator1(str[i]) && str[i+1]=='=') && (isalnum(str[i+2]) || isnumber(str[i+2])))
		    {
			i=i+2;			                      
		    }
		    else if(isoperator(str[len-1]))
		    {
			printf("invalid operator is inserted\n");
			exit(0);
		    }
		    else if(isoperator1(str[len-2]) && str[len-1]=='=')
		    {
			printf("invalid operator is inserted\n");
			exit(0);
		   }
		}
		else
		{
		    printf("invalid expression\n");
		    exit(0);
		}



	}
	//printf("valid expression\n");
	return 1;
	 }
	 else
	     printf("invalid Parenthesis is inserted\n");
	return 0;
}


void postfix(char s[])
{
	
	int len,i=0,j=0;
	len=strlen(s);
	char temp;
	char postfix[2*len];
	printf("\nthe infix expression is %s",s);
     while(s[i]!='\0')
	 {
	 	if(s[i]=='(')
	 	{
	 		push(s[i]);
	 		i++;
		}
		else if(isalnum(s[i]))
		{
			postfix[j++]=s[i++];
			postfix[j++]=' ';
			
		}
		else if(isnumber(s[i]))
	 	{
	 		while(isnumber(s[i]))
            {
            	postfix[j++]=s[i++];
			}
			postfix[j++]=' ';	 		
		 }
                  else if(isoperator1(s[i]) && s[i+1]=='=')
		 {
		     while(isoperator1(s[i]) && s[i+1] == '=' && precedence2(stack[top]) > precedence(s[i]))
		     {
			 postfix[j++]=pop1();
			 postfix[j++]=pop1();
			 postfix[j++]=' ';
		     }
		     push(s[i+1]);
		     push(s[i]);
		     i=i+2;
		 }

		 else if(isoperator(s[i]))
		 {
		 	
		 	while(isoperator(s[i])==1 && precedence(stack[top])>precedence(s[i]))
            {
			   postfix[j++]=pop1();
			   postfix[j++]=' ';
			}		 	
		 	push(s[i++]);
		 	
		 }
		 
		 else if(s[i]==')')
		 {
		        temp=pop1();
		 	while(temp!='(')
		 	{
		 		postfix[j++]=temp;
		 		temp=pop1();
			 }
			 i++;
		 }
	 }	
	 while(top > -1)
	 {
	 	postfix[j++] = pop1();
	 }
	 postfix[j]='\0';
	 printf("\nthe postfix expression is:%s",postfix);
}


int main()
{
	char str1[100];
	printf("enter the infix expression--> ");
	gets(str1);
	if(validateInfix(str1) == 1)
	{
		postfix(str1);
	}
	return 0;
}
