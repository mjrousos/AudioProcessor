#include <stdio.h>

bool KeepListening;
FILE* ecasoundStdIn;
pid_t jackCtlPID;
const char* QJackCtlCommandLine = "/usr/local/bin/qjackctl";
const char* EcasoundCommandLineBase = "/usr/local/bin/ecasound -c -i jack,system -o ";

bool StartJackCtl();
bool EndJackCtl();
bool ArmRecording();
bool DisarmRecording();
bool StartRecording();
bool StopRecording();
void StopListening();
void Log(const char* msg);
void ShowUsage();