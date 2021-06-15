#include<stdio.h>

int main(int argc, char *argv[]) {
    // Hardcoded intentionally; the binary is bundled with the Windows VM.
    char flag[] = "FS{binaries_schminaries_part_deuce}";

    printf("Great job. Here is your flag: \n");
    printf("%s\n", flag);

    // Never used
    char never_used[] = "Yes - this flag is readable by strings. However, if you understand strings, we assume you understand how to do these simple tasks.";

    // pause before exit
    printf("Press Enter to continue...\n");
    getchar();

    return 0;
}

