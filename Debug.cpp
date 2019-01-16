#include "Debug.h"

void RegisterDebugCallback(DebugCallback callback)
{
	callbackFunction = callback;
}

void Debug::Log(const char* message, Color color)
{
	if (callbackFunction != nullptr)
	{
		callbackFunction(message, (int)color, (int)strlen(message));
	}
}

void Debug::Log(const std::string message, Color color)
{
	const char* tmsg = message.c_str();
	if (callbackFunction != nullptr)
	{
		callbackFunction(tmsg, (int)color, (int)strlen(tmsg));
	}
}

void Debug::Log(const int message, Color color)
{
	std::stringstream ss;
	ss << message;
	SendLog(ss, color);
}

void Debug::Log(const char message, Color color)
{
	std::stringstream ss;
	ss << message;
	SendLog(ss, color);
}

void Debug::Log(const float message, Color color)
{
	std::stringstream ss;
	ss << message;
	SendLog(ss, color);
}

void Debug::Log(const double message, Color color)
{
	std::stringstream ss;
	ss << message;
	SendLog(ss, color);
}

void Debug::Log(const bool message, Color color)
{
	std::stringstream ss;
	if (message)
	{
		ss << "true";
	}
	else
	{
		ss << "false";
	}
	SendLog(ss, color);
}

void Debug::SendLog(const std::stringstream &ss, const Color &color)
{
	const std::string temp = ss.str();
	const char* tmsg = temp.c_str();
	if (callbackFunction != nullptr)
	{
		callbackFunction(tmsg, (int)color, (int)strlen(tmsg));
	}
}