#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#if WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Controller.h"

#if !WINDOWS
void Sleep(int seconds) { sleep(seconds); }
#endif

int main()
{
    Log("Audio controller starting");
    
    // Begin qjackctl
    Sleep(2);
    
    // Begin ecasound
    Sleep(2);
    
    KeepListening = true;
    
    Log("Ready!"); // TODO : Notify of readiness via GPIO
    
    // !! TEMPORARY TEST!
    BeginRecording();
    // !! TEMPORARY TEST!
    
    while (KeepListening)
    {
        // Listen for start/stop from the GPIO pins
        Sleep(0.5); // Sleep some so that we're not thrashing in this loop
    }        
    
    Log("Audio controller ending");
    return 0;
}

void BeginRecording()
{
    // Create file name
    time_t t = time(NULL);
    tm* localTime = (localtime(&t));
    char outputFile[4096]; // TODO : Replace this with platform-appropriate consts
    sprintf(outputFile, "Out_%d-%d-%d_%d-%d-%d.wav", (1900 + localTime->tm_year), localTime->tm_mon, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    
        
    Log("Recording to:");
    Log(outputFile);
}

void EndRecording()
{
    
}

void StopListening()
{
    KeepListening = false;
}

const int TIME_STR_LEN = 28;
void Log(const char* msg)
{
    time_t t = time(NULL);
    char* timeStr = asctime(localtime(&t));
    timeStr[strlen(timeStr) - 1] = '\0'; // asctime automatically  includes an unwanted new line; so get rid of it
    printf("[%s] %s\n", timeStr, msg);
}