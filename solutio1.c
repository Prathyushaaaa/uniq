#include "types.h"
#include "user.h"

#define BUFFER_SIZE 1536

/* function prototypes */
void clear_arr(char *a, int size);
int getstr(int filed, char *buffer, int maximum);
char toUpper(char lc);
int stricmp(const char *p, const char *q);
void error(char* str);
void uniq_c(int filed, int ipswitch);
void uniq_d(int filed, int ipswitch);
void uniq_n(int filed, int ipswitch);
void uniq(int filed, int ipswitch, int cpswitch, int dpswitch);

void uniq(int filed, int ipswitch, int cpswitch, int dpswitch)
{
    if(cpswitch)
        uniq_c(filed, ipswitch);
    if(dpswitch)
        uniq_d(filed, ipswitch);
    if(!cpswitch && !dpswitch)
        uniq_n(filed, ipswitch);
}

void uniq_c(int filed, int ipswitch)
{
    char mainstring[BUFFER_SIZE], backup[BUFFER_SIZE];
    int count = 0, flag = 0;
    int (*strcmp_f[])(const char *,const char*) = {&strcmp, &stricmp};

    clear_arr(backup, BUFFER_SIZE);
    clear_arr(mainstring, BUFFER_SIZE);
    if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
        return;
    strcpy(backup, mainstring);
    while(1)
    {
        while((*strcmp_f[ipswitch])(mainstring, backup) == 0)
        {
            clear_arr(mainstring, BUFFER_SIZE);
            count++;
            if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            printf(1, "%d %s", count, backup);
            return;
        }
        printf(1, "%d %s", count, backup);
        count = 0;
        strcpy(backup, mainstring);
    }
}

void uniq_d(int filed, int ipswitch)
{
    char mainstring[BUFFER_SIZE], backup[BUFFER_SIZE];
    int flag = 0;
    int (*strcmp_f[])(const char *,const char*) = {&strcmp, &stricmp};

    clear_arr(backup, BUFFER_SIZE);
    while(1)
    {
        clear_arr(mainstring, BUFFER_SIZE);
        if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
            return;
        if((*strcmp_f[ipswitch])(mainstring, backup) != 0)
            strcpy(backup, mainstring);
        else
        {
            while((*strcmp_f[ipswitch])(mainstring, backup) == 0)
            {
                clear_arr(mainstring, BUFFER_SIZE);
                if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
            {
                printf(1, "%s", backup);
                return;
            }
            printf(1, "%s", backup);
            strcpy(backup, mainstring);
        }
    }
}

void uniq_n(int filed, int ipswitch)
{
    char mainstring[BUFFER_SIZE], backup[BUFFER_SIZE];
    int (*strcmp_f[])(const char *,const char*) = {&strcmp, &stricmp};

    clear_arr(backup, BUFFER_SIZE);
    while(1)
    {
        clear_arr(mainstring, BUFFER_SIZE);
        if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
            return;
        while((*strcmp_f[ipswitch])(mainstring, backup) == 0)
        {
            clear_arr(mainstring, BUFFER_SIZE);
            if(getstr(filed, mainstring, BUFFER_SIZE) <= 0)
                return;
        }
        printf(1, "%s", mainstring);
        strcpy(backup, mainstring);
    }
}

int getstr(int filed, char *buffer, int maximum)
{
    int i, cc;
    char c;

    for(i = 0; i + 1 < maximum; )
    {
        cc = read(filed, &c, 1);
        if(cc < 1)
        return -1;
    buffer[i++] = c;
    if(c == '\n' || c == '\r')
         break;
    }

    buffer[i] = '\0';
    return strlen(buffer);
}

int stricmp(const char *p, const char *q)
{
    while(*p && toUpper(*p) == toUpper(*q))
        p++, q++;
    return (uchar)*p - (uchar)*q;
}

char toUpper(char lc)
{
    if(lc >= 'a' && lc <= 'z')
        return lc - ('a' - 'A');
    else
        return lc;
}

void clear_arr(char *a, int size)
{
    int i;

    for(i = 0; i < size; i++)
        a[i] = '\0';
}

void error(char* str)
{
    printf(1, "Error: %s. Terminating\n", str);
    exit();
}

int main (int argc, char *argv[])
{
    int filed, j, ckfl;
    int i = 0, c = 0, d = 0;

    for(j = 1; j < argc; j++)
    {
        if(argv[j][0] == '-')
        {
            switch(argv[j][1])
            {
                case 'i':
                    i = 1;
                    break;
                case 'd':
                    d = 1;
                    break;
                case 'c':
                    c = 1;
                    break;
                default:
                    error("Unexpected option, this ain't legal, please try again");
            }
        }
    }

    for(j = 1, ckfl = 0; j < argc; j++)
    {
        if(argv[j][0] != '-')
        {
            ckfl = 1;
            break;
        }
    }

    if(!ckfl)
    {
        uniq(0, i, c, d);
        exit();
    }

    for(j = 1; j < argc; j++)
    {
        if(argv[j][0] == '-')
            continue;
        else if((filed = open(argv[j], 0)) < 0)
        {
            printf(1, "uniq: cannot open file %s\n", argv[j]);
            exit();
        }
        if(c && d)
            error("both c and d cannot be used simultaneously. sorry, this ain't legal.");
      printf(1,"Filename: %s\n", argv[j]);
        uniq(filed, i, c, d);
        close(filed);
    }
    exit();
}
