#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char text[] = "abcdedcba";
    int length = strlen(text);
    bool rep = true;
    for (int i = 0; i < length / 2; i++) {
        if (text[i] != text[length - 1 - i]) {
            break;
            rep = false;
        }
    }
    if(rep)
    	printf("true");
    else
    	printf("false");
    return 0;
}
