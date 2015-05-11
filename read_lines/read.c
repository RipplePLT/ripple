#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

    ssize_t read;
    size_t len = 0;

    char *line;
    FILE *fp = fopen("hello.txt", "r");
    while(1){
	    while ((read = getline(&line, &len, fp)) != -1) {
	        printf("%s", line);
	        sleep(1);
	    }
	    fseek(fp, SEEK_SET, 0);
	}
    fclose(fp);

    return 0;
}