#include <stdio.h>
#include <stdlib.h>
#include <shlToSml.h>
int main(int argc, char *argv[])
{
	int check = 1;
	if(argc <= 1)
	{
		printf("\n\t\a %s ERROR : No input file!!! %s \n","\x1B[36m","\x1B[0m");
		exit(1);
	}
	else if(argc > 2)
	{
		printf("\n\t\a %s ERROR : More than 1 input file!!! %s \n","\x1B[36m","\x1B[0m");	
		exit(1);
	}
	

	check = shlToSml(argv[1]);
	
	if(check == 0)
		printf("\n\t\a %s ‎SUCCESS | SML file is created ( sml.txt ) %s \n\n","\x1B[35m","\x1B[0m");
	else
		exit(1);
return 0;
}