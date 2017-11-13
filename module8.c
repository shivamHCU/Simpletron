#include "module8.h"


struct tableEntry 
{
   int symbol;
   char type; /* 'C', 'L' or 'V' */    
   int location; /* 00 to 99 */
};

tableEntry symbolTable[100];


int mainMemory[100] = {0};
int flag[100][2] = {0};
unsigned int symbolTableCounter = 0;
unsigned int variableMemoryCounter = 99;
unsigned int smlLineCounter = 0;

int searchSymbolTable(int location)
{
   for(int i=0;i<symbolTableCounter;i++)
   {
      if(symbolTable[i].location == location)
         return 1;
   }
   return 0;
}


void addToSymbolTable(int s,char t,int l )
{
   
   symbolTable[symbolTableCounter].symbol = s;
   symbolTable[symbolTableCounter].type = t;
   symbolTable[symbolTableCounter].location = l;
   symbolTableCounter++;
}

int lookInToSymboltable(int sym,char t)
{

   for(int i = 0 ; i < symbolTableCounter ; i++ )
   {
      if(symbolTable[i].type == t && symbolTable[i].symbol == sym)
           return symbolTable[i].location;
   }

return 00;
}


int searchInVariableMemoryMap(int map[][2],int varMapLen,int mem)
{
   for (int i = 0; i < varMapLen; ++i)
   {
      if(map[i][0] == mem)
         return map[i][1];
   }
return mem;   
}


void printSymbolTable()
{
   printf("\n length of symbolTable : %d \n",symbolTableCounter );
   printf("\n\t\tsymbol\t\ttype\t\tlocation\n");
   printf("\n\t\t------------------------------------------\n");
   for(int i = 0 ; i < symbolTableCounter ; i++ )
   {
      if(symbolTable[i].type == 'V')
         printf("\n\t\t%2c\t\t%2c\t\t%02d",(char)symbolTable[i].symbol,symbolTable[i].type,symbolTable[i].location);
      else
         printf("\n\t\t%02d\t\t%2c\t\t%02d",symbolTable[i].symbol,symbolTable[i].type,symbolTable[i].location);         
      
   }

   printf("\n");

}
