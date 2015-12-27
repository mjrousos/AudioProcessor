#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Controller.h"

int main()
{
    Log("Audio controller starting");
    Log("Audio controller ending");
    return 0;
}

const int TIME_STR_LEN = 28;
void Log(const char* msg)
{
    time_t t = time(NULL);
    char timeStr[TIME_STR_LEN];
    asctime_s(timeStr, TIME_STR_LEN, localtime(&t));
    timeStr[strlen(timeStr) - 1] = '\0'; // asctime automatically  includes an unwanted new line; so get rid of it
    printf("[%s] %s\n", timeStr, msg);
}