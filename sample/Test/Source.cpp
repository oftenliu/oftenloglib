#include"opr_log.h"

#define TEST_ERROR(format,...)  LOG("test",LOG_ERROR_, format,__VA_ARGS__)

int main()
{
	Opr_InitLog("log4cplus.properties");
	TEST_ERROR("often:test my log lib ÎÒ°®Äã");
	
	system("pause");

	return 0;
}

