#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include "Time.h"

class ErrorLog
{
public:

	/// <summary>
	/// The log file name
	/// </summary>
	std::string logFileName = "..//JADE2D.log";
	/// <summary>
	/// The SeverityLevel Enum of the ErrorLog
	/// </summary>
	enum SeverityLevel
	{
		JADE_NONE,		// NO ERROR
		JADE_INFO,		// LOAD-UP SEQUENCE
		JADE_WARNING,	// WARNING BUT OK TO CONTINUE
		JADE_ERROR,		// ERROR
		JADE_TRACE		// ERROR TRACE
	};

	/// <summary>
	/// Finalizes an instance of the <see cref="ErrorLog"/> class.
	/// </summary>
	~ErrorLog();
	/// <summary>
	/// Gets the instance.
	/// </summary>
	/// <returns></returns>
	static ErrorLog * getInstance()
	{
		if (instance == nullptr)
		{
			instance = new ErrorLog;
		}
		return instance;
	}
	/// <summary>
	/// Closes this instance.
	/// </summary>
	void close();
	/// <summary>
	/// Logs the specified severity.
	/// </summary>
	/// <param name="severity">The severity.</param>
	/// <param name="message">The message.</param>
	void log(SeverityLevel severity, const std::string&  message);
	/// <summary>
	/// Sets the log file.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	void setLogFile(const std::string& fileName);
	/// <summary>
	/// Sets the severity setting of the LogManager, only
	///	those messages whose severity is greater than
	///	or equal to this severity will be added to the log.
	/// </summary>
	/// <param name="severity">The minimum severity of messages to print.</param>
	void setSeverity(SeverityLevel severity) { m_currentSeverity = severity; }
	/// <summary>
	/// Returns the current severity of the ErrorLog
	/// </summary>
	/// <returns></returns>
	SeverityLevel getSeverity() { return m_currentSeverity; }
	/// <summary>
	/// Errors the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void error(const std::string& message);
	/// <summary>
	/// Warnings the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void warning(const std::string& message);
	/// <summary>
	/// Traces the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void trace(const std::string& message);
	/// <summary>
	/// Informations the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void info(const std::string& message);
	/// <summary>
	/// Sets up log.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	void setUpLog(const std::string& fileName);
	/// <summary>
	/// Gets the time.
	/// </summary>
	/// <returns></returns>
	std::string getTime() { setRealTime(); return m_time; }

private:
	/// <summary>
	/// The instance of this class
	/// </summary
	static ErrorLog * instance;
	/// <summary>
	/// The m_output stream
	/// </summary>
	std::ofstream * m_outputStream = nullptr;
	/// <summary>
	/// The log was setup
	/// </summary>
	bool logWasSetup = false;
	/// <summary>
	/// The m_current severity
	/// </summary>
	SeverityLevel m_currentSeverity = JADE_NONE;

	/// <summary>
	/// Sets the real time.
	/// </summary>
	void setRealTime()
	{
		time_t temp = (time_t)Time::getTime();
		char str[32];
		m_time = ctime_s(str, sizeof(str), &temp);
	}

	/// <summary>
	/// The num_ errors
	/// </summary>
	int Num_Errors = 0;

	/// <summary>
	/// The m_time
	/// </summary>
	std::string m_time;

	/// <summary>
	/// Prevents a default instance of the <see cref="ErrorLog"/> class from being created.
	/// </summary>
	ErrorLog() {}
};

