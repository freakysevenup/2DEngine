// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 01-30-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 01-30-2016
// ***********************************************************************
// <copyright file="ErrorLog.cpp" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
// </summary>
// ***********************************************************************

#include "ErrorLog.h"
#include <sys/stat.h>
#include <memory>

/// <summary>
/// The instance{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
ErrorLog * ErrorLog::instance = nullptr;

ErrorLog::~ErrorLog()
{
	Close();
}

void ErrorLog::Close()
{
	if (m_outputStream != nullptr)
	{
		m_outputStream->close();
		delete m_outputStream;
		m_outputStream = nullptr;
	}
}

void ErrorLog::Log(SeverityLevel severity, const std::string& message)
{
	SetSeverity(severity);

	std::string severityLevel;
	switch (severity)
	{
	case JADE_NONE:
		severityLevel = "JADE_NONE";
		break;
	case JADE_INFO:
		severityLevel = "JADE_INFO";
		break;
	case JADE_ERROR:
		severityLevel = "JADE_ERROR";
		break;
	case JADE_WARNING:
		severityLevel = "JADE_WARNING";
		break;
	case JADE_TRACE:
		severityLevel = "JADE_TRACE";
		break;
	}

	if (m_outputStream == nullptr)
	{
		SetLogFile(logFileName);
		SetUpLog(logFileName);
	}
	Num_Errors++;
	(*m_outputStream) << "Error # : " << std::to_string(Num_Errors) << "\n"
		<< "Time Occured : " << GetTime() << "\n"
		<< "Error Severity : " << severityLevel << "\n"
		<< "Error Message : " << "\n"
		<< "---------------------------------------------" << "\n"
		<< message << "\n"
		<< "---------------------------------------------" << "\n\n";

	m_outputStream->flush();

}

void ErrorLog::SetLogFile(const std::string& fileName)
{
	Close();
	logWasSetup = false;

	// Create Directory for Saving this log file if one does not already exist
	// Works on Windows and UNIX systems
	system("mkdir .\\ErrorLog\\");

	//Getting an Error here, create a LogFiles directory.
	m_outputStream = new std::ofstream(std::string(".\\ErrorLog\\") + fileName.c_str());
	SetUpLog(fileName);
	m_currentSeverity = JADE_NONE;
}

void ErrorLog::Error(const std::string& message)
{
	Log(JADE_ERROR, message);
}

void ErrorLog::Warning(const std::string& message)
{

	Log(JADE_WARNING, message);
}

void ErrorLog::Trace(const std::string& message)
{
	Log(JADE_TRACE, message);
}

void ErrorLog::Info(const std::string& message)
{
	Log(JADE_INFO, message);
}

void ErrorLog::SetUpLog(const std::string& fileName)
{
	if (!logWasSetup)
	{
		Num_Errors = 0;
		(*m_outputStream) << fileName << "\n" << "----------------- Error Log from JADE -----------------" << "\n";
		logWasSetup = true;
	}
}