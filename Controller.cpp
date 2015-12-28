#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Controller.h"

int main()
{
    Log("Audio controller starting");
    
    StartJackCtl();
    
    if (0 != ArmRecording())
    {
        Log("ERROR: Arming failed");
        return -1;
    }
    
    KeepListening = true;
    
    Log("Ready!"); // TODO : Notify of readiness via GPIO
    
    // !! TEMPORARY TEST!
    StartRecording();
    sleep(3);
    StopRecording();
    // !! TEMPORARY TEST!
    
    while (KeepListening)
    {
        // Listen for start/stop from the GPIO pins
        usleep(500000); // Sleep some so that we're not thrashing in this loop
        
        // TODO : TEMPORARY TEST
        StopListening();
    }        
    
    DisarmRecording();
    EndJackCtl();
    
    Log("Audio controller ending");
    EndJackCtl();
    
    return 0;
}

void StartJackCtl()
{
    sleep(2);
}

void EndJackCtl()
{
    // TODO
}

int ArmRecording()
{
    // Create file name
    time_t t = time(NULL);
    tm* localTime = (localtime(&t));
    char outputFile[PATH_MAX];
    sprintf(outputFile, "Out_%d-%d-%d_%d-%d-%d.wav", (1900 + localTime->tm_year), localTime->tm_mon, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    // Assemble command line
    char ecasoundCommandLine[PATH_MAX];
    strcpy(ecasoundCommandLine, EcasoundCommandLineBase); // TODO : Guard against overruns
    strcat(ecasoundCommandLine, outputFile); // TODO : Guard against overruns

    // Begin ecasound
    ecasoundStdIn = popen(ecasoundCommandLine, "w");
    if (!ecasoundStdIn)
    {
        Log("ERROR starting ecasound");
        return -1;
    }
    sleep(2);
    Log("Recording armed");
    Log("Output file set to:");
    Log(outputFile);
    
    return 0;
}

void DisarmRecording()
{
    if (ecasoundStdIn)
    {
        fprintf(ecasoundStdIn, "q\n");
        fflush(ecasoundStdIn);
        pclose(ecasoundStdIn);
        Log("Recording disarmed");
    }
}

void StartRecording()
{
    if (ecasoundStdIn)
    {
        fprintf(ecasoundStdIn, "t\n");
        fflush(ecasoundStdIn);
        Log("Recording started");
    }
}

void StopRecording()
{
    if (ecasoundStdIn)
    {
        fprintf(ecasoundStdIn, "s\n");
        fflush(ecasoundStdIn);
        Log("Recording stopped");
    }
}

void StopListening()
{
    KeepListening = false;
    Log("Stopped listening for triggers");
}

const int TIME_STR_LEN = 28;
void Log(const char* msg)
{
    time_t t = time(NULL);
    char* timeStr = asctime(localtime(&t));
    timeStr[strlen(timeStr) - 1] = '\0'; // asctime automatically  includes an unwanted new line; so get rid of it
    printf("[%s] %s\n", timeStr, msg);
}