#include <stdbool.h>
#include <stdio.h>


int main()
{
	char c;
	bool oneAlready = false;
	long int curPos;
	int charsToRemove = 2;
	
	FILE* f = fopen("test.c", "r+");
	
	while ((c = getc(f)) != EOF)
	{
		if (c == '/')
		{
			if (oneAlready)
			{
				while ((c = getc(f)) != '\n')
					charsToRemove++;
					
				curPos = ftell(f);
				fseek(f, curPos - charsToRemove - 1, SEEK_SET);
				
				for (int i = 0; i < charsToRemove; i++)
					fprintf(f, " ");
				oneAlready = false; continue;
			}
			oneAlready = true;
		}
	}		
	fclose(f);
	return 0;
}
