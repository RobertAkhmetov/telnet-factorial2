#include <stdio.h>
#include <stdlib.h>

int factor(int);

int main (int argc, char* argv[]) {
if (argc > 1) {
int temp = atoi(argv[1]);
printf("%d! = %d\n", temp, factor(temp)); }
return 0;
}
int factor(int src) {
if ((src == 1)||(src == 0))
return 1;
else
return src*factor(src-1);
}
