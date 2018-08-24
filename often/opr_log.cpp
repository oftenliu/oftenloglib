#include"opr_log.h"
#include <io.h>
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/helpers/stringhelper.h>


using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

bool g_bStarted = false;


log4cplus::LogLevel Translate_LogLevel(const LOG_LEVEL level);
log_string Parse_Va_Param(const char* pFormat, va_list args);


std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);

static log_string ws2t(const std::wstring ws);


std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}




static log_string ws2t(const std::wstring ws)
{
#if UNICODE
	return ws;
#else
	return ws2s(ws);
#endif
}

static log_string s2t(const std::string s)
{
#if UNICODE
	return s2ws(s);
#else
	return s;
#endif
}

static std::string t2s(const log_string s)
{
#if UNICODE
	return ws2s(s);
#else
	return s;
#endif
}



DLL_PUBLIC int Opr_InitLog(const char* pPropertiesFile)
{
	if (pPropertiesFile == NULL || strlen(pPropertiesFile) < 1)
	{
		return -1;
	}


	if (g_bStarted)
	{
		return 0;
	}

	if (_access(pPropertiesFile, 0) == -1)//is exist   
	{
		return -1;
	}

	initialize();
	const log4cplus::tstring tsScriptFile = LOG4CPLUS_C_STR_TO_TSTRING(pPropertiesFile);
	PropertyConfigurator::doConfigure(tsScriptFile);

	SharedAppenderPtrList appendList = log4cplus::Logger::getRoot().getAllAppenders();
	if (appendList.size() == 0)  //if root logger undefine Append
	{
		// create appender object. default output the log to console
		log4cplus::Logger::getRoot().setLogLevel(ALL_LOG_LEVEL);
		SharedObjectPtr<Appender> append(new ConsoleAppender());
		append->setName(LOG4CPLUS_TEXT("ConsoleAppender"));

		// set appender layout */
		log4cplus::tstring pattern = LOG4CPLUS_TEXT("[%D{%Y-%m-%d %H:%M:%S,%Q}] [%t %c %-5p] %m%n");
		append->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
		log4cplus::Logger::getRoot().addAppender(append);
		printf(" use the default append");
	}

	g_bStarted = true;
	return 0;
}



DLL_PUBLIC void Opr_DoLog(const char* pModule,
	const LOG_LEVEL nLevel,
	const char* pFilename,
	const char* pFunction,
	const int pFileline,
	const char* pFormat, ...)
{
	if (nLevel > LOG_FATAL_ || nLevel < LOG_TRACE_)
	{
		return;
	}

	if (NULL == pModule || NULL == pFilename || NULL == pFunction || NULL == pFormat)
	{
		return;
	}
	Logger logger;

	if (log4cplus::Logger::exists(LOG4CPLUS_C_STR_TO_TSTRING(pModule)))
	{
		logger = log4cplus::Logger::getInstance(LOG4CPLUS_C_STR_TO_TSTRING(pModule));
	}
	else
	{
		logger = log4cplus::Logger::getRoot();
	}

	char acTmp[32] = { 0 };
	sprintf(acTmp, "%d", pFileline);

	va_list args;
	std::string strLog = "[" + std::string(pFilename) + " " + std::string(pFunction) + "(" + std::string(acTmp) + ")] ";

	va_start(args, pFormat);
	strLog += Parse_Va_Param(pFormat, args);
	va_end(args);

	int nLog4cplus_Level = Translate_LogLevel(nLevel);
	switch (nLog4cplus_Level)
	{
	case log4cplus::TRACE_LOG_LEVEL:
		LOG4CPLUS_TRACE(logger, LOG4CPLUS_TEXT(strLog));
		break;
	case log4cplus::DEBUG_LOG_LEVEL:
		LOG4CPLUS_DEBUG(logger, LOG4CPLUS_TEXT(strLog));
		break;
	case log4cplus::INFO_LOG_LEVEL:
		LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT(strLog));
		break;
	case log4cplus::WARN_LOG_LEVEL:
		LOG4CPLUS_WARN(logger, LOG4CPLUS_TEXT(strLog));
		break;
	case log4cplus::ERROR_LOG_LEVEL:
		LOG4CPLUS_ERROR(logger, LOG4CPLUS_TEXT(strLog));
		break;
	case log4cplus::FATAL_LOG_LEVEL:
		LOG4CPLUS_FATAL(logger, LOG4CPLUS_TEXT(strLog));
		break;
	default:
		break;
	}

	return;
}


log4cplus::LogLevel Translate_LogLevel(const LOG_LEVEL level){

	switch (level) {
	case(LOG_LEVEL::LOG_TRACE_) :
		return log4cplus::TRACE_LOG_LEVEL;
	case(LOG_LEVEL::LOG_DEBUG_) :
		return log4cplus::DEBUG_LOG_LEVEL;
	case(LOG_LEVEL::LOG_INFO_) :
		return log4cplus::INFO_LOG_LEVEL;
	case(LOG_LEVEL::LOG_WARN_) :
		return log4cplus::WARN_LOG_LEVEL;
	case(LOG_LEVEL::LOG_ERROR_) :
		return log4cplus::ERROR_LOG_LEVEL;
	case(LOG_LEVEL::LOG_FATAL_) :
		return log4cplus::FATAL_LOG_LEVEL;
	default:
		return log4cplus::WARN_LOG_LEVEL;
	}
}




log_string Parse_Va_Param(const char* pFormat, va_list args)
{
	if (NULL == pFormat)
	{
		return _LOG_T("");
	}

	int iNum = 0;
	unsigned int uiSize = 1024;
	log_string strLog(_LOG_T(""));

	log_char *pcBuff = new(std::nothrow) log_char[uiSize];
	if (NULL == pcBuff)
	{
		return strLog;
	}

	while (true)
	{
		memset(pcBuff, 0, uiSize);
		iNum = log_vsnwprintf_s(pcBuff, sizeof(pcBuff) / sizeof (log_char), uiSize, pFormat, args);
		_vsnwprintf_s(pcBuff, sizeof(pcBuff) / sizeof (log_char), uiSize, pFormat, args);
		if ((iNum > -1) && (iNum < (int)uiSize))
		{
			strLog = pcBuff;
			SAFE_DELETE(pcBuff);
			return strLog;
		}

		//如果字符串值比默认分配大，则分配更大空间
		uiSize = (iNum > -1) ? (int)(iNum + 1) : (uiSize * 2);
		SAFE_DELETE(pcBuff);

		pcBuff = new(std::nothrow) log_char[uiSize];
		if (NULL == pcBuff)
		{
			return strLog;
		}
	}

	SAFE_DELETE(pcBuff);
	return strLog;
}

DLL_PUBLIC void Opr_FiniLog()
{
	Logger::shutdown();
	g_bStarted = false;
}


