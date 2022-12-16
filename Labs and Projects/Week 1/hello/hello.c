#include <stdio.h>

int main(void)
{
    char name[30];
    printf("Write your name:");
    scanf("%s", name);
    printf("hello, %s\n", name);
}