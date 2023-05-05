#include "_Imports.h"

TM GT()
{
	time_t t = time(NULL);
	return *localtime(&t);
}

void tprint()
{
	TM Time = GT();
	printf("[ %d-%d | %d:%d:%d ]\t", Time.tm_mon, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec);
}

void tprintf(char *string)
{
	tprint();
	printf("%s\n", string);
}

void teprintf(char *string)
{
	tprint();
	perror(string);
}

void tcprintw(char *string)
{
	printw("]=======$ %s\n", string);
}
void twprint()
{
	TM Time = GT();
	printw("[ %d-%d | %d:%d:%d ]\t", Time.tm_mon, Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec);
}
void tprintw(char *string)
{
	tprint();
	printw("%s\n", string);
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

	while (size[i] != '\0')
	{
		if (size[i] >= 48 && size[i] <= 57)
		{
			res = res * 10 + (size[i] - 48);
		}

		i++;
	}

	return res;
}

void strtolower(char *res, const char *str)
{
	if (str == NULL)
		return;

	int c = 0;
	while (str[c] != '\0')
		c++;

	if (res != NULL)
		free(res);
	res = malloc((c + 1) * sizeof(char));
	c = 0;
	do
	{
		res[c] = tolower(str[c]);
		c++;
	} while (str[c] != '\0');
}

void strtolower_s(char *strtolow)
{
	char *str;
	strcpy(str, strtolow);
	strtolower(strtolow, str);
	free(str);
}

char *r_newline(char *str)
{
	char *re = strchr(str, '\n');
	re[0] == '\n' ? re[0] = ' ' : (re[0] = re[0]);

	return str;
}

int strcmpi(const char *str1, const char *str2)
{
	char *s_str1, *s_str2;
	strcpy(s_str1, str1);
	strtolower_s(s_str1);
	strcpy(s_str2, str2);
	strtolower_s(s_str2);

	int re = strcmp(s_str1, s_str2);
	free(s_str1);
	free(s_str2);
	return re;
}

void fscan(char *string)
{
	scanf("%[^\n]%*c", string);
}

void ChangeColor(COLOR Color)
{
	printf(Color);
}

int IsInAllowedChars(char c)
{
	if (c >= 32 && c <= 57)
		return 1;
	if (c >= 63 && c <= 90)
		return 1;
	if (c >= 95 && c <= 122)
		return 1;

	return 0;
}