#ifndef _OPR_LOG_DEFINE_
#define _OPR_LOG_DEFINE_

#include<string>
#include <stdio.h>
#include <stdlib.h>


#include <stdarg.h>
using namespace std;


#if defined(_WIN32) || defined(_WIN64) 
#ifdef _LOGIB_EXPORTS_
#define DLL_PUBLIC __declspec(dllexport)
#else
#define DLL_PUBLIC __declspec(dllimport)
#endif
#endif

#define SAFE_DELETE(v_para)\
do \
{\
	if (NULL != v_para) \
	{\
		delete[] v_para; \
		v_para = NULL; \
	}\
} while (0)







//TRACE < DEBUG < INFO < WARN < ERROR < FATAL
typedef enum _LOG_LEVEL
{
	LOG_TRACE_ = 0,
	LOG_DEBUG_,
	LOG_INFO_,
	LOG_WARN_,
	LOG_ERROR_,
	LOG_FATAL_
}LOG_LEVEL;



#define OPR_ERROR(format,...)  LOG("OPR",LOG_ERROR_, format,__VA_ARGS__)
#define OPR_INFO(format,...)   LOG("OPR",LOG_INFO_, format,__VA_ARGS__)
#define OPR_TRACE(format,...)  LOG("OPR",LOG_TRACE_, format,__VA_ARGS__)
#define OPR_DEBUG(format,...)  LOG("OPR",LOG_DEBUG_, format,__VA_ARGS__)
#define OPR_WARN(format,...)   LOG("OPR",LOG_WARN_, format,__VA_ARGS__)
#define OPR_FATAL(format,...)  LOG("OPR",LOG_FATAL_, format,__VA_ARGS__) 


#define LOG(module,level, format,...) Opr_DoLog(module,level, __FILE__, __FUNCTION__, __LINE__, format,__VA_ARGS__)

/*
* Opr_InitLog
*Brief: initialize log lib 
*IN pPropertiesFile: Log Lib configuration file
*OUT: NULL
*/
DLL_PUBLIC int Opr_InitLog(const char* pPropertiesFile);



/*
*Opr_DoLog
*Brief: write log 
*IN pModule: 日志模块名，指配置文件中append
*IN nLevel: 日志级别
*IN pFilename: 调用Opr_DoLog的当前源文件
*IN pFunction: 当前函数
*IN pFileline: 行号
*IN pFormat: 打印日志的格式 如： "%s%d%f"
*IN ...: 可变输入
*OUT: NULL
*/
DLL_PUBLIC void Opr_DoLog(const char* pModule,
	const LOG_LEVEL nLevel,
	const char* pFilename,
	const char* pFunction,
	const int pFileline,
	const char* pFormat, ...);


/*
* Opr_FiniLog
*Brief: uninitialize log lib
*OUT: NULL
*/
DLL_PUBLIC void Opr_FiniLog();

#endif
