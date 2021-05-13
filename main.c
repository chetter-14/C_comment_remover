#include <stdbool.h>
#include <stdio.h>
#include <string.h>


int main()
{
	char c;
	bool oneAlready = false;
	
	FILE* f = fopen("test.c", "r+");
	
	while ((c = getc(f)) != EOF)
	{
		if (c == '/')
		{
			if (oneAlready)
				putc(
			oneAlready = true;
		}	
	}		
	return 0;
}
