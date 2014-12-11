#pragma once

class Logger
{

public:
	static Logger& Instance()
	{
		static Logger logger;
		return logger;
	}
	
	bool LogMessage(CString message);
	bool LogError(CString message);
	bool LogException(CString message);
	
private:
	Logger() {};
	Logger(const Logger&);
	Logger& operator=(const Logger&);

	bool Log(CString message);
};
