/*
MIT License

Copyright (c) 2021 Rodrigo Bento

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32
#error This library targets Microsoft Windows only
#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG

////////////////////////////////////////////////////////////////////////////////

#define NOOP ((void)0)

#define Trace(Format, ...) NOOP
#define Debug(Format, ...) NOOP
#define  Info(Format, ...) NOOP
#define  Warn(Format, ...) NOOP 
#define Error(Format, ...) NOOP
#define Fatal(Format, ...) NOOP

////////////////////////////////////////////////////////////////////////////////

#else

////////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUT_DEBUG_FORMAT_LENGTH
#define _OUTPUT_DEBUG_FORMAT_LENGTH 384
#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUT_DEBUG_STRING_LENGTH
#define _OUTPUT_DEBUG_STRING_LENGTH 1024
#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef _WINDOWS_
#undef APIENTRY
#include <windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <unordered_map>
#include <string>

////////////////////////////////////////////////////////////////////////////////

#define printf OutputDebugF /** printf outputs to Visual Studio Output window */

////////////////////////////////////////////////////////////////////////////////

enum class OutputDebugLevel 
{
	Message, Trace, Debug, Info, Warn, Error, Fatal
};

////////////////////////////////////////////////////////////////////////////////

static const OutputDebugLevel _OUTPUT_DEBUG_LEVEL = OutputDebugLevel::Trace;

////////////////////////////////////////////////////////////////////////////////

#define Trace(Format, ...) OutputDebug(OutputDebugLevel::Trace, Format, __VA_ARGS__)
#define Debug(Format, ...) OutputDebug(OutputDebugLevel::Debug, Format, __VA_ARGS__)
#define  Info(Format, ...) OutputDebug(OutputDebugLevel::Info,  Format, __VA_ARGS__)
#define  Warn(Format, ...) OutputDebug(OutputDebugLevel::Warn,  Format, __VA_ARGS__)
#define Error(Format, ...) OutputDebug(OutputDebugLevel::Error, Format, __VA_ARGS__)
#define Fatal(Format, ...) OutputDebug(OutputDebugLevel::Fatal, Format, __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////

static int __stdcall OutputDebugVA(const char* Format, va_list Args)
{
	char CharBuffer[_OUTPUT_DEBUG_STRING_LENGTH];
	int NumCharsWritten = vsnprintf(CharBuffer, sizeof(CharBuffer), Format, Args);

	OutputDebugStringA(CharBuffer);

	return NumCharsWritten;
}

////////////////////////////////////////////////////////////////////////////////

static int __stdcall OutputDebugF(const char* Format, ...)
{
	va_list Args;
	va_start(Args, Format);

	int NumCharsWritten = OutputDebugVA(Format, Args);

	va_end(Args);

	return NumCharsWritten;
}

////////////////////////////////////////////////////////////////////////////////

static int __stdcall OutputDebug(OutputDebugLevel Level, const char* Format, ...)
{
	static std::unordered_map<OutputDebugLevel, const char*> Markers
	{
		{ OutputDebugLevel::Trace, "TRC" },
		{ OutputDebugLevel::Debug, "DBG" },
		{ OutputDebugLevel::Info, "INF" },
		{ OutputDebugLevel::Warn, "WRN" },
		{ OutputDebugLevel::Error, "ERR" },
		{ OutputDebugLevel::Fatal, "FTL" }
	};

	if (Level < _OUTPUT_DEBUG_LEVEL)
	{
		return 0;
	}

	char MarkedFormat[_OUTPUT_DEBUG_FORMAT_LENGTH];
	sprintf_s(MarkedFormat, "%s %s\n", Markers[Level], Format);

	va_list Args;
	va_start(Args, Format);

	int NumCharsWritten = OutputDebugVA(MarkedFormat, Args);

	va_end(Args);

	return NumCharsWritten;
}

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////