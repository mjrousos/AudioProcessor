#include <stdio.h>

bool KeepListening;
FILE* ecasoundStdIn;
pid_t jackCtlPID;
const char* QJackCtlCommandLine = "/usr/local/bin/qjackctl";
const char* EcasoundCommandLineBase = "/usr/local/bin/ecasound -c -i jack,system -o ";

void StartJackCtl();
void EndJackCtl();
int ArmRecording();
void DisarmRecording();
void StartRecording();
void StopRecording();
void StopListening();
void Log(const char* msg);