#include<stdio.h>

#define SHELLSCRIPT1 "ifconfig  | grep 'inet ' | awk {'print $2'} | sed 1q >> myip.txt"
#define SHELLSCRIPT2 "rm myip.txt"
int main(){
	char output[256];
	puts(SHELLSCRIPT1);
	system(SHELLSCRIPT1);

	FILE * ptr = fopen("myip.txt", "r");
	fscanf(ptr, "%s", output);
	puts(SHELLSCRIPT2); system(SHELLSCRIPT2);
	printf(output); 
	return 0;
}
