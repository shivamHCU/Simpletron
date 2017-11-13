#include "module8.h"
#include "module7.h"
#include "module6.h"
#include "module5.h"
#include "shlToSml.h"

/*
 NRM -> "\x1B[0m"
 RED -> "\x1B[31m"
 GRN -> "\x1B[32m"
 YEL -> "\x1B[33m"
 BLU -> "\x1B[34m"
 MAG -> "\x1B[35m"
 CYN -> "\x1B[36m"
 WHT -> "\x1B[37m"
*/


int shlToSml(char *fname)
{
   
   FILE *shlChecker = fopen(fname, "r");
   int ERROR = shlcheckerfunc(shlChecker);
   if( ERROR == 1)
   {  
         printf("\n\n\t\t%s!!! SYNTAX ERRORS !!! %s  \n","\x1B[31m","\x1B[34m");
         system("cat error.txt");
         printf("%s\n","\x1B[0m");
         return 1;
   }

   FILE *fin;
   FILE *fout;
   char *line = NULL;
   size_t len = 0;
   ssize_t read;
   const char *delimiter_characters = " \n\t";
   char *lastToken;
   int  tokenCount = 0; 
   
   fin = fopen(fname, "r");
   
   fout = fopen("sml.txt", "w+");
   
   if (fin == NULL)
   {
   	printf("\n\t\a %s '%s' file can't be read !!! %s \n","\x1B[31m",fname,"\x1B[0m");
   	return 1;
   }   
   if (fout == NULL)
   {
		printf("\n\t\a %s '%s' file can't be open !!! %s \n","\x1B[31m","sml.txt","\x1B[0m");
      return 1;
   } 
   int i = 0 ;
   char *tokenArray[40];
   int *instructionList ;
   
   while ((read = getline(&line, &len, fin)) != -1)
   {
      
      lastToken = strtok( line, delimiter_characters );
      
      i=0; 
      while( lastToken != NULL )
      {
         tokenArray[i++] = (char *) lastToken;
         lastToken = strtok( NULL, delimiter_characters );
      }   
      
      addToSymbolTable(atoi(tokenArray[0]),'L',smlLineCounter);

      switch(tokenArray[1][0])
      {
         case 'l' :
                        if(lookInToSymboltable((int)tokenArray[2][0],'V') == 0)
                              addToSymbolTable((int)tokenArray[2][0],'V',variableMemoryCounter--);
                        
                        int lengthOfString = strlen(tokenArray[2]) ;
                        if(validateInfix(tokenArray[2]) == 0)
                        {
                           tokenArray[2] = convertToPostfix(tokenArray[2]);
                           instructionList = convertToSML(tokenArray[2]);                        
                           //coping the returned instruction from module 7 to mainMemory
                           for (int i = 0; i < smlInstructionCounter ; ++i)
                           {
                              mainMemory[smlLineCounter++] = smlInstruction[i];   
                           }
                        }
                        else
                        {   
                           printf("\n\t %s ERROR @ %d: Invalid Expression !!! %s \n","\x1B[31m",atoi(tokenArray[0]),"\x1B[0m");
                           return 1;
                        }
                        break;
         case 'p' :
                        mainMemory[smlLineCounter] = (11*100)+lookInToSymboltable((int)tokenArray[2][0],'V');
                        smlLineCounter++;
                        break;
         case 'i' :  
                        
                        switch(tokenArray[1][1])
                        {
                              case 'n' :   

                                             addToSymbolTable((int)tokenArray[2][0],'V',variableMemoryCounter--);
                                             mainMemory[smlLineCounter] = (10*100) + variableMemoryCounter + 1;
                                             smlLineCounter++;
                                             break;
                              case 'f' :   

                                             if(validateInfix(tokenArray[2]) == 0)
                                             {
                                                
                                                tokenArray[2] = convertToPostfix(tokenArray[2]);
                                                instructionList = convertToSML(tokenArray[2]);                        
                                                for (int i = 0; i < smlInstructionCounter ; ++i)
                                                {
                                                      mainMemory[smlLineCounter++] = smlInstruction[i];   
                                                }   
                                                if(mainMemory[smlLineCounter-1] / 100 == 41 || mainMemory[smlLineCounter-1] / 100 == 42 )
                                                {
                                                   mainMemory[smlLineCounter-1] += lookInToSymboltable(atoi(tokenArray[4]),'L');
                                                      if(mainMemory[smlLineCounter - 1]%100 == 0)
                                                      {
                                                         flag[smlLineCounter - 1][0] = 1;
                                                         flag[smlLineCounter - 1][1] = atoi(tokenArray[4]);
                                                      }
                                                   
                                                   if(mainMemory[smlLineCounter-2] / 100 == 42)
                                                   {
                                                      mainMemory[smlLineCounter-2] += lookInToSymboltable(atoi(tokenArray[4]),'L');
                                                      if(mainMemory[smlLineCounter - 2]%100 == 0)
                                                      {
                                                         flag[smlLineCounter - 2][0] = 1;
                                                         flag[smlLineCounter - 2][1] = atoi(tokenArray[4]);
                                                      }
                                                   }
                                                }
                                                else if(mainMemory[smlLineCounter-1] / 100 == 40 &&  mainMemory[smlLineCounter-2] /100 == 42)
                                                {
                                                   mainMemory[smlLineCounter-1] += lookInToSymboltable(atoi(tokenArray[4]),'L');
                                                   mainMemory[smlLineCounter-2] += smlLineCounter + 1;

                                                   if(mainMemory[smlLineCounter - 1]%100 == 0)
                                                   {
                                                      flag[smlLineCounter - 1][0] = 1;
                                                      flag[smlLineCounter - 1][1] = atoi(tokenArray[4]);
                                                   }

                                                }
                                             }
                                             else
                                             {  
                                                printf("\n\t %s ERROR @ %d: Invalid Expression !!! %s \n","\x1B[31m",atoi(tokenArray[0]),"\x1B[0m"); 
                                            	   return 1;
                                             } 
                                             break;  
                              default :
                                          printf("\n\n\t%s!!!  ERROR : Command Not Found !!! %s \n","\x1B[31m","\x1B[0m");
                                          return 1;

                        } 
                        break;   
         case 'g' :   

                        mainMemory[smlLineCounter] = (40*100) + lookInToSymboltable(atoi(tokenArray[2]),'L') ;
                        
                        if(mainMemory[smlLineCounter]%100 == 0)
                        {
                           flag[smlLineCounter][0] = 1;
                           flag[smlLineCounter][1] = atoi(tokenArray[2]);
                        }
                        
                        smlLineCounter++;   
                        break;

         case 'e' :   
                        mainMemory[smlLineCounter] = 4300;
                        smlLineCounter++;
                        break;
         case 'r' :   
                        // Nothing to do it here as it ia a remark

                        break;               
         default:
                        printf("\n\n\t%s!!!  ERROR : Command Not Found !!! %s \n","\x1B[31m","\x1B[0m");
                        return 1;
      }




   }

   int variableMemoryMap[100][2];
   int varMapLen = 99 - variableMemoryCounter;
         
   for(int i = 0 ; i < varMapLen ; i++)
   {
      
      mainMemory[smlLineCounter] =  mainMemory[99-i];
      variableMemoryMap[i][0] = 99 - i; 
      variableMemoryMap[i][1] = smlLineCounter;
      smlLineCounter++;
   }

   int addr,actualAddr;
   for(int i = 0 ; i < smlLineCounter - varMapLen ; i++)
   {
      if(flag[i][0] == 1)
      {  
         addr = mainMemory[i]%100;
         actualAddr = lookInToSymboltable(flag[i][1],'L');
         mainMemory[i] = ((mainMemory[i] / 100 ) * 100 )+ actualAddr;   
      }
      else
      {
         addr = mainMemory[i]%100;
         actualAddr = searchInVariableMemoryMap(variableMemoryMap,varMapLen,addr); 
         mainMemory[i] = ((mainMemory[i] / 100 ) * 100 )+ actualAddr;
      } 
   } 
   
   for (int i = 0; i < smlLineCounter ; ++i)
   {
      if(mainMemory[i] < 0)
      {
         fprintf(fout,"%02d     %05d\n", i, mainMemory[i]);
      }
      else
      {
         fprintf(fout,"%02d     +%04d\n", i, mainMemory[i]);
      }
   }

   free(line);
   fclose(fin);
   fclose(fout);

return 0;
}