#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 128
#define DC(str)  do { char * ptr = str ; while (*ptr) *ptr++ -= 0x01; } while(0)

// This function repurposed from code provided by:
// http://www.codingunit.com Programming Tutorials

// Just some function prototypes.
int Parse_and_Compare_from_Command(char *cmd, char *str);

// Our main function.
int main(int argc, char *argv[]) {
    char cmd[] = "ipconfig";
    char cmd_result[] = "192.168.2.102";
    char flag[] = "{{encoded_flag}}";
    DC(flag);
    char incorrect[] = "Double check your network address - it is not ";

    int result, errno;

    result = Parse_and_Compare_from_Command(cmd, cmd_result);
    if (result == -1) {
        perror("Error");
        printf("Error number = %d\n", errno);
        exit(1);
    }
    else if (result == 0){
        printf("%s%s.\n", incorrect, cmd_result);
    }
    else
    {
        printf("Great job. Here is your flag: \n");
        printf("%s\n", flag);
    }

    // Never used
    char never_used[] = "Yes -  this flag is readable by strings. However, if you understand strings, I assume you understand how to do these simple tasks.";

    // pause before exit
    printf("Press Enter to continue...\n");
    getchar();
    return(0);
}

int Parse_and_Compare_from_Command(char *cmd, char *str) {
    //char *cmd = "ls -l";

    char buf[BUFSIZE];
    int find_result = 0;
    FILE *fp;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
        if((strstr(buf, str)) != NULL) {
            find_result++;
        }
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    if(find_result == 0) {
        //printf("\nSorry, couldn't find a match.\n");
        return 0;
    }
    else {
        //printf("A match found on line.\n");
        return 1;
    }
}
