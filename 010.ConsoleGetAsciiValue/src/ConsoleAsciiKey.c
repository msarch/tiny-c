// returns ascii code of one key and exits
// dependencies : stdio.h, conio.h
// linker : -lconio

#include <stdio.h>
#include <conio.h>
void main()
{
char c;
c=getch();
printf("%d\n",c);
getch();
}