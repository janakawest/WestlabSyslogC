/**
	* WestLab syslog class
	* This has been designed based on the following resources
	* RFC5424 				: https://tools.ietf.org/html/rfc5424
	* syslog man page	: https://linux.die.net/man/3/openlog
  * online resources: http://stackoverflow.com/questions/2638654/redirect-c-stdclog-to-syslog-on-unix 
*/

/**
	* //Create a global char array 
	* char message[100]; 
	* 
	* OpenSyslog (argv[0], user); // Passing the program name as the syslog entry name
	* sprintf (message, "This is from Thread:%d, I am executing on the CPU_ID:%d\n",10, 10);
	* ToWestlabLog (debug, message); // Specify the log type. Note that this version distinguishs only DEBUG messages.
																	 // All other types are referred to as INFO.
																	 // Therefore, the type should be either 'debug' or some another.
	* ToWestlabLog (info, "Creating Threads"); 
	* // Note: you have to close the syslog at the end of your program.
	* CloseLog ();*/

#include "westSysLogC.c"

void OpenSyslog (char *name, enum LogType type)
{
	openlog(name, LOG_PID|LOG_CONS/*|LOG_PERROR*/, type);
}

void CloseLog ()
{
	closelog ();
}
