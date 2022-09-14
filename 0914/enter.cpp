#include <stdio.h>

int main() {
	while(1) {
		char c;
		scanf("%c", &c);
		if(c == '\n')
			break;
	}
	printf("Good bye");
	return 0;
}
