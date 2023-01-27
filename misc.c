#include "_Imports.h"

TM GT()
{
	time_t t = time(NULL);
	return *localtime(&t);
}

void tprintf(char *string)
{
	TM Time = GT();
	printf("\n[ %d-%d | %d:%d:%d ]\t", Time.tm_mon, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec);
	printf("%s", string);
}

void teprintf(char *string)
{
	tprintf("");
	perror(string);
}

void checkerr(int res, char *MsgIfErr)
{
	if (res < 0)
	{
		teprintf(MsgIfErr);
		exit(EXIT_FAILURE);
	}
}

void FByteSize(char *string, char *Re_Size)
{
	char re[5];
	char *check = string;
	int count = 0;
	while (*check != '\0')
	{
		count++;
		check++;
	}
	if (count <= 9)
	{
		sprintf(Re_Size, "000%d", count);
	}
	else if (count <= 99)
	{
		sprintf(Re_Size, "00%d", count);
	}
	else if (count <= 999)
	{
		sprintf(Re_Size, "0%d", count);
	}
	else if (count <= 9999)
	{
		sprintf(Re_Size, "%d", count);
	}
	else
	{
		sprintf(Re_Size, "9999");
	}
}

int FBSizeToInt(char *FBSize)
{
	char *size = FBSize;
	int i = 0, res = 0;

	while (size != "\0")
	{
		if (size[i] >= 48 && size[i] <= 57)
		{
			res = res * 10 + (size[i] - 48);
		}
		else
			return -1;
	}
	return res;
}

void fscan(char *string)
{
	scanf("%[^\n]%*c", string);
}
