#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void printFileProperties(struct stat stats) {
    struct tm dt;

    printf("\nFile access: ");
    if (stats.st_mode & S_IRUSR) printf("read ");
    if (stats.st_mode & S_IWUSR) printf("write ");
    if (stats.st_mode & S_IXUSR) printf("execute");

    printf("\nFile size: %ld bytes", stats.st_size);

    dt = *(gmtime(&stats.st_ctime));
    printf("\nCreated on: %d-%d-%d %d:%d:%d",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);

    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %d-%d-%d %d:%d:%d\n",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);
}

int main() {
    char fname[100];
    struct stat stats;

    printf("Enter the file name: ");
    scanf("%s", fname);

    if (stat(fname, &stats) == 0) {
        printFileProperties(stats);
    } else {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", fname);
    }

    return 0;
}
