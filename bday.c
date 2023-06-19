#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#define OFFSET 5
#define SMOKE_HEIGHT 7

#define COLOR_BOLD "\e[1m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

int rand_range(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

void print_offset(char *s, int add)
{
    char of[OFFSET + 1 + add]; // +1 for terminating zero
    for (int i = 0; i < OFFSET + add; i++)
    {
        of[i] = ' ';
    }
    of[OFFSET + add] = '\0';

    // printf("%d from: |%s|\n", OFFSET+add, of);
    printf(of);
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c", s[i]);
        if (s[i] == '\n')
        {
            printf("%s", of);
        }
    }
    printf("\n");
}

void cake()
{
    char *s =
        "     |       |\n"
        "     |       |\n"
        "     ---------\n"
        " ____/       \\____\n"
        "|       " COLOR_BOLD COLOR_GREEN "מזל  " COLOR_RESET "     |\n"
        "|  " COLOR_BOLD COLOR_GREEN "     טוב   " COLOR_RESET "    |\n"
        "|    " COLOR_BOLD COLOR_GREEN "   אבא  " COLOR_RESET "     |\n"
        "-------------------";

    print_offset(s, 0);
}

void candle()
{
    char *s =
        "  .'.\n"
        "  | |\n"
        "__|_|__";

    char *a = "  " COLOR_YELLOW "(\\" COLOR_RESET;
    char *b = "   " COLOR_YELLOW "/)" COLOR_RESET;

    int which = rand_range(0, 1);
    int o = 6;
    if (which)
    {
        print_offset(a, o);
    }
    else
    {
        print_offset(b, o);
    }

    print_offset(s, o);
}

void smoke(int offset, char c)
{

    int move = rand_range(offset, offset + 2);
    for (int i = 0; i < move; i++)
    {
        printf(" ");
    }

    printf("%c\n", c);
}

long long sec_to_u(float t)
{
    return t * 1000000;
}

long long time_in_usec()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void u_sleep(long long t)
{
    long long start, stop;
    start = time_in_usec();
    stop = time_in_usec();
    while ((stop - start) < t)
    {
        stop = time_in_usec();
    }
}

void s_sleep(float t)
{
    u_sleep(sec_to_u(t));
}

void star()
{
    int r = rand_range(0, 20);
    for (int i = 0; i < r; i++)
    {
        printf(" ");
    }
    printf("*\n");
}

int main()
{
    printf("hello world\n");
    int count = 0;

    // print_offset("this is a test");
    int next_visible = 1;
    while (1)
    {
        printf("\e[1;1H\e[2J");
        printf("%d\n", count++);

        smoke(6, '+');
        smoke(8, '+');
        smoke(9, '+');
        smoke(10, '+');
        if (next_visible)
        {
            smoke(11, '+');
        }
        else
        {
            printf("\n");
        }
        if (rand_range(0, 1))
        {
            next_visible = 1;
            smoke(12, '+');
        }
        else
        {
            next_visible = 0;
            printf("\n");
        }

        candle();
        cake();

        s_sleep(0.3);
        fflush(stdout);
    }

    return 0;
}
