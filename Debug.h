#pragma once

#include <stdio.h>
#include <string>
#include <sstream>

// Call this function from a Untiy script
extern "C"
{
	typedef void(*DebugCallback)(const char* message, int color, int size);
	static DebugCallback callbackFunction = nullptr;
	__declspec(dllexport) void RegisterDebugCallback(DebugCallback callback);
}

enum class Color { Red, Green, Blue, Black, White, Yellow, Orange};

class Debug
{
public:
	// Call these functions from within the plugin to send error messages to the Unity Debug.Log function
	static void Log(const char* message, Color color = Color::Black);
	static void Log(const std::string message, Color color = Color::Black);
	static void Log(const int message, Color color = Color::Black);
	static void Log(const char message, Color color = Color::Black);
	static void Log(const float message, Color color = Color::Black);
	static void Log(const double message, Color color = Color::Black);
	static void Log(const bool message, Color color = Color::Black);

private:
	static void SendLog(const std::stringstream &ss, const Color &color);
};