#include <stdbool.h>
#include <stdio.h>
#define COM_CHARS_AMOUNT 2  // amount of comment chars (// and /* are two chars in length)


int main()
{
	char c;
	bool firstSlashWasMet = false, firstAsterWasMet = false;
	bool secAsterWasMet = false, secSlashWasMet = false;
	bool isEndOfComment = false;
	long int curPos, firstSlashPos, firstAsterPos, secSlashPos, secAsterPos;
	int charsToRemove = COM_CHARS_AMOUNT;
	
	FILE* f = fopen("test.c", "r+");
	
	while ((c = getc(f)) != EOF)
	{
		if (c == '/')
		{
			if (firstSlashWasMet)
			{
				secSlashPos = ftell(f);
				if (secSlashPos - firstSlashPos == 1)
				{			
					while ((c = getc(f)) != '\n')
						charsToRemove++;
						
					fseek(f, firstSlashPos - 1, SEEK_SET);
					for (int i = 0; i < charsToRemove; i++)
						fprintf(f, " ");
						
					firstSlashWasMet = false;
					charsToRemove = COM_CHARS_AMOUNT;
					continue;
				}
				continue;
			}
			firstSlashWasMet = true;
			firstSlashPos = ftell(f);
			continue;
		}
		if (c == '*' && firstSlashWasMet)
		{
			firstAsterPos = ftell(f);
			if (firstAsterPos - firstSlashPos == 1)
			{
				fseek(f, firstAsterPos, SEEK_SET);
				while (!isEndOfComment && ((c = getc(f)) != EOF))
				{
					if (c == '*')
					{
						secAsterWasMet = true;
						secAsterPos = ftell(f);
					}
					if (c == '/' && secAsterWasMet)
					{
						secSlashPos = ftell(f);
						if (secSlashPos - secAsterPos == 1)
							isEndOfComment = true;
					}
					charsToRemove++;
				}
				fseek(f, firstSlashPos - 1, SEEK_SET);
				
				for (int i = 0; i < charsToRemove; i++)
					fprintf(f, " ");
				charsToRemove = COM_CHARS_AMOUNT;
			}
		}
	}		
	fclose(f);
	return 0;
}
