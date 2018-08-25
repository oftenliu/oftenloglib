#include"opr_log.h"

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/helpers/stringhelper.h>


#define TEST_ERROR(format,...)  LOG("test",LOG_ERROR_, format,__VA_ARGS__)
#define TEST_INFO(format,...)  LOG("test",LOG_INFO_, format,__VA_ARGS__)
#define TEST_WAEN(format,...)  LOG("test",LOG_WARN_, format,__VA_ARGS__)
#define TEST_DEBUG(format,...)  LOG("test",LOG_DEBUG_, format,__VA_ARGS__)
#define TEST_FATAL(format,...)  LOG("test",LOG_FATAL_, format,__VA_ARGS__)
#define TEST_TRACE(format,...)  LOG("test",LOG_TRACE_, format,__VA_ARGS__)
int main()
{
	Opr_InitLog("log4cplus.properties");
	TEST_ERROR("often:test my log lib 我爱你");
	TEST_ERROR("often:test my log lib 元亨利贞");
	TEST_INFO("often:test my log lib 潜龙，勿用。");
	TEST_WAEN("often:test my log lib 见龙在田，利见大人。");
	TEST_DEBUG("often:test my log lib 君子终日乾乾，夕惕若厉,无咎。");
	TEST_FATAL("often:test my log lib 或跃在渊，无咎");
	TEST_TRACE("often:test my log lib 九五：飞龙在天，利见大人。");
	system("pause");
	return 0;
}

