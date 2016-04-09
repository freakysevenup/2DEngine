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

/// <summary>
/// The instance{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
ErrorLog * ErrorLog::instance = nullptr;

ErrorLog::~ErrorLog()
{
	close();
}

void ErrorLog::close()
{
	if (m_outputStream != nullptr)
	{
		m_outputStream->close();
		delete m_outputStream;
		m_outputStream = nullptr;
	}
}

void ErrorLog::log(SeverityLevel severity, const std::string& message)
{
	if (severity > JADE_NONE)
	{
		setSeverity(severity);
	}

	if (severity >= m_currentSeverity && m_currentSeverity > JADE_NONE)
	{
		if (m_outputStream == nullptr)
		{
			setLogFile(logFileName);
			setUpLog(logFileName);
		}
		Num_Errors++;
		(*m_outputStream) << "Error # : " << std::to_string(Num_Errors) << "\n"
			<< "Time Occured : " << getTime() << "\n"
			<< "Error Message : " << "\n"
			<< "---------------------------------------------" << "\n"
			<< message << "\n"
			<< "---------------------------------------------" << "\n";

		m_outputStream->flush();
	}
}

void ErrorLog::setLogFile(const std::string& fileName)
{
	close();
	logWasSetup = false;
	std::string path = "./LogFiles/";
	//Getting an Error here, create a LogFiles directory.
	m_outputStream = new std::ofstream(path + fileName.c_str());
	setUpLog(fileName);
	m_currentSeverity = JADE_ERROR;
}

void ErrorLog::error(const std::string& message)
{
	log(JADE_ERROR, message);
}

void ErrorLog::warning(const std::string& message)
{

	log(JADE_WARNING, message);
}

void ErrorLog::trace(const std::string& message)
{
	log(JADE_TRACE, message);
}

void ErrorLog::info(const std::string& message)
{
	log(JADE_INFO, message);
}

void ErrorLog::setUpLog(const std::string& fileName)
{
	if (!logWasSetup)
	{
		Num_Errors = 0;
		(*m_outputStream) << fileName << "\n" << "----------------- Error Log from JADE -----------------" << "\n";
		logWasSetup = true;
	}
}