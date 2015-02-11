#include "Exception.h"

//void Exception::FillStackTrace()
//{
//	//linux下
//
//	//window下
//}

const char * Exception::what() const throw()
{
	return message_.c_str(); //c_str()转换为char *
}

//const char * Exception::StackTrace() const throw()
//{
//
//	return stackTrace_.c_str();
//}
