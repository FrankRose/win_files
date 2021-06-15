#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 128
#define DC(str)  do { char * ptr = str ; while (*ptr) *ptr++ -= 0x01; } while(0)

// This function repurposed from code provided by:
// http://www.codingunit.com Programming Tutorials

//Just some function prototypes.
void Usage(char *filename);
int Parse_and_Compare_from_Command(char *cmd, char *str);

//Our main function.
int main(int argc, char *argv[]) {
  char cmd[] = "ping 8.8.8.8";
  char cmd_result[] = "Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)";
  char flag[] = "{{encoded_flag}}";
DC(flag);
  char incorrect[] = "Double check that you have outside network connectivity. You should be able to browse to www.google.com.";

	int result, errno;
  //if(argc < 3 || argc > 3) {
	if(argc > 1) {
		Usage(argv[0]);
		//exit(1);
	}

	//Use system("cls") on windows
	//Use system("clear") on Unix/Linux
	//system("clear");

  printf("Wait for it - this may take up to 5 secs.\n");
	result = Parse_and_Compare_from_Command(cmd, cmd_result);
	if(result == -1) {
		perror("Error");
		printf("Error number = %d\n", errno);
		exit(1);
	}
  else if (result == 0){
    printf("%s\n", incorrect);
  }
  else
  {
    printf("Great job. Here is your flag: \n");
    printf("%s\n", flag);
  }
  // Never used
  char never_used[] = "Yes -  this flag is readable by strings. However, if you understand strings, I assume you understand how to do these simple tasks.";
  // pause before exit
  printf("Press any key to continue...\n");
  getchar();  // or getchar()
  return(0);
}

void Usage(char *filename) {
	printf("Usage: %s [no inputs needed]\n", filename);
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
