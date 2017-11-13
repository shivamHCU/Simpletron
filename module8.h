#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int mainMemory[100] ;
extern int flag[100][2] ; 

extern unsigned int symbolTableCounter ;  
extern unsigned int variableMemoryCounter ; 
extern unsigned int smlLineCounter ;

struct tableEntry ;
typedef struct tableEntry tableEntry;

void addToSymbolTable(int, char , int );// used to add line/caonstant/variable in symbol table 

int lookInToSymboltable(int ,char); // Searches a symbol in symbol table

int searchInVariableMemoryMap(int [][2], int, int ); // function used to search in variable memory mapping 

void printSymbolTable(); //prints symbol table for teseting purposes

int searchSymbolTable(int ); // Searches a location in symol table
