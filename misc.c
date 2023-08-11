#include "_Imports.h"

void RESET_THREAD()
{
	int re;
	if ((re = pthread_self()) == (int)SERVER_THREAD)
		SERVER_STATE--;
	else if (re == (int)(CLIENT_THREAD[0]))
		CLIENTS_STATE--;
	else if (re == (int)(CLIENT_THREAD[1]))
		CLIENTS_STATE -= 10;
}

int snd(int sockfd, void *buf, size_t len, int flags)
{
	int re;
	if ((re = send(sockfd, buf, len, MSG_NOSIGNAL | flags)) < 0)
	{
		buf = malloc(len * sizeof(char));
		clt_lnk clt;
		clt_find_local_sock(sockfd, &clt);
		if (clt != NULL)
			clt_disconnect(clt);
		RESET_THREAD();
		pthread_exit(0);
	}

	return re;
}

int rcv(int *sockfd, void *buf, size_t len, int flags)
{
	int re;
	if ((re = recv(*sockfd, buf, len, flags)) <= 0)
	{
		clt_lnk clt;
		clt_find_local_sock(*sockfd, &clt);
		if (clt != NULL)
			clt_disconnect(clt);

		RESET_THREAD();
		pthread_exit(0);
	}

	return re;
}

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
char *zero_show(int x)
{
	if (x < 10)
		return "0";
	else
		return "";
}
void tsprint(char *dest)
{
	TM Time = GT();
	sprintf(dest, "%s%d-%s%d | %s%d:%s%d:%s%d", zero_show(Time.tm_mon), Time.tm_mon, zero_show(Time.tm_mday), Time.tm_mday, zero_show(Time.tm_hour), Time.tm_hour, zero_show(Time.tm_min), Time.tm_min, zero_show(Time.tm_sec), Time.tm_sec);
}

void checkerr(int res, char *MsgIfErr)
{
	if (res < 0)
	{
		debug_sys_cnsle_log();
		endwin();
		system("clear");
		printf("Error : %s", MsgIfErr);

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

int AddNUllChar(char *Str)
{
	int nullpos= 0;
	for(int i = 0; IsValidChar(Str[i]) && i < strlen(Str); i++)
		nullpos = i;

	Str[nullpos + 1 ] = '\0';
	return nullpos;		
}

int IsValidChar(char c)
{
	if (c >= 0 && c <= 127)
		return 1;

	return 0;
}