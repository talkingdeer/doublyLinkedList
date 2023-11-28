#pragma once
#include <string.h>

class myException
{
	char message[256];
	int code;
	public:
	myException(const char *msg, int c)
	{
		code = c;
		strncpy(message, msg, 255);
	}

	const char *getMessage() const
	{
		return message;
	}

	int getCode()
	{
		return code;
	}
};

enum errorCodes
{
	EC_MEMORY = -1,
	EC_FILE = -2,
	EC_MATRIX = -3
};
