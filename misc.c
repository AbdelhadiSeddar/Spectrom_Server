#include "_Imports.h"

struct tm GT() {
    time_t t = time(NULL);
    return *localtime(&t);
}

void tprintf(char* string){
    struct tm Time = GT();
    printf("[ %d-%d | %d:%d:%d ]\t", Time.tm_mon,Time.tm_mday, Time.tm_hour, Time.tm_min, Time.tm_sec);
    printf("%s\n", string);
}

void teprintf(char* string){
    tprintf("");
    perror(string);
}


//Gets the size of the message in a 4 Byte Sequence; 
// Note Returns 9999 if Size if too large;
void FByteSize(char* string, char* Re_Size){
	char re[4];
    char* check = string;
    int count = 0;
    while(*check != '\0'){
        count++;
        check++;
    }
	if(count <= 9){
		sprintf(Re_Size, "000%d", count);
	}
	else if (count <= 99){
		sprintf(Re_Size, "00%d", count);
	}
	else if (count <= 999){
		sprintf(Re_Size, "0%d", count);
	}
	else if(count <= 9999){
		sprintf(Re_Size, "%d", count);
	}
	else{
		sprintf(Re_Size, "9999");
	}
}

void fscan(char* string){
	scanf("%[^\n]%*c", string);
}
