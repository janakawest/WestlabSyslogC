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
#ifndef SYSLOG_WEST
#define SYSLOG_WEST

#include <syslog.h>
#include <string.h>


//namespace WestlabSyslog
//{
/**
	* This is according to RFC5424.
		 Numerical         Severity
			 Code

				0       Emergency: system is unusable
				1       Alert: action must be taken immediately
				2       Critical: critical conditions
				3       Error: error conditions
				4       Warning: warning conditions
				5       Notice: normal but significant condition
				6       Informational: informational messages
				7       Debug: debug-level messages

				Table 2. Syslog Message Severities
	* **/
	enum LogLevel
	{
    emergency = LOG_EMERG,
    alert     = LOG_ALERT,
    critical  = LOG_CRIT,
    error     = LOG_ERR,
    warning   = LOG_WARNING,
    notice    = LOG_NOTICE,
    info      = LOG_INFO,
    debug     = LOG_DEBUG,
	};
/**
	* This is according to RFC5424
	  Numerical             Facility
		 Code

			0             kernel messages
			1             user-level messages
			2             mail system
			3             system daemons
			4             security/authorization messages
			5             messages generated internally by syslogd
			6             line printer subsystem
			7             network news subsystem
			8             UUCP subsystem
			9             clock daemon
		 10             security/authorization messages
		 11             FTP daemon
		 12             NTP subsystem
		 13             log audit
		 14             log alert
		 15             clock daemon (note 2)
		 16             local use 0  (local0)
		 17             local use 1  (local1)
		 18             local use 2  (local2)
		 19             local use 3  (local3)
		 20             local use 4  (local4)
		 21             local use 5  (local5)
		 22             local use 6  (local6)
		 23             local use 7  (local7)

		Table 1.  Syslog Message Facilities
	However, according to the openlog(3) - Linux man page, it supports only following types
*/	
	enum LogType
	{
		auth   	= LOG_AUTH,
		authPriv=	LOG_AUTHPRIV,
		cron   	= LOG_CRON,
		log_daemon 	= LOG_DAEMON,
		ftp			=	LOG_FTP,
		kern		= LOG_KERN,
	  local0 	= LOG_LOCAL0,
    local1 	= LOG_LOCAL1,
    local2 	= LOG_LOCAL2,
    local3 	= LOG_LOCAL3,
    local4	= LOG_LOCAL4,
    local5 	= LOG_LOCAL5,
    local6 	= LOG_LOCAL6,
    local7 	= LOG_LOCAL7,
		lpr			= LOG_LPR,
    mail   	= LOG_MAIL,
    news   	= LOG_NEWS,
		wsyslog	= LOG_SYSLOG,
    user   	= LOG_USER,
    uucp   	= LOG_UUCP,
		
		/*clockd	=	LOG_CLOCK,
		ntp			=	LOG_NTP,
		logaudit=	LOG_AUDIT,
		logalert=	LOG_ALERT,
    print  	= LOG_LPR,*/
	};
//} //End of the namespace

// The macro to write into Syslog
// Specify the log type. Note that this version distinguishs only DEBUG messages.
// All other types are referred to as INFO.
// Therefore, the type should be either 'debug' or some another.
#define ToWestlabLog(LOGTYPE, TEXT) LOGTYPE==debug?syslog (LOG_INFO, "Function: %s Line: %d File: %s: %s", __func__, __LINE__, __FILE__, TEXT):syslog (LOG_INFO, "%s", TEXT);

// Concatenate the File name from the absolute path
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
void OpenSyslog (char *name, enum LogType type)
{
	openlog(name, LOG_PID|LOG_CONS/*|LOG_PERROR*/, type);
}

void CloseLog ()
{
	closelog ();
}
#endif // SYSLOG_WEST
