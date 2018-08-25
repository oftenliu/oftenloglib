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
	TEST_ERROR("often:test my log lib �Ұ���");
	TEST_ERROR("often:test my log lib Ԫ������");
	TEST_INFO("often:test my log lib Ǳ�������á�");
	TEST_WAEN("often:test my log lib ��������������ˡ�");
	TEST_DEBUG("often:test my log lib ��������ǬǬ��Ϧ������,�޾̡�");
	TEST_FATAL("often:test my log lib ��Ծ��Ԩ���޾�");
	TEST_TRACE("often:test my log lib ���壺�������죬�������ˡ�");
	system("pause");
	return 0;
}

