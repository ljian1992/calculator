/*********************************************************************************
*FileName: SymbolTable.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:26:44
*Description :
主要功能：定义了该工程中所用要的异常处理类
	语法异常---->SyntaxError类
		赋值时左操作数不是变量：1 = 2;
		缺少括号：1 + (2*2
		不认识的函数：
		函数缺少括号：sin(20
		符号表中不存在的符号：
		输入一个变量但没有设置它的值：a 回车
		不是表达式：)1-2
	文件读写异常---->FileStreamError类
		文件读异常
		文件写异常
	除零异常--->DevisorZero类
	加载时与存储的版本号不一致--->VersionUnMatch类
**********************************************************************************/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
	std::string message_;                         //异常信息
	//std::string stackTrace_;
	//void FillStackTrace();

public:
	explicit Exception(const char* message)        //char *类型赋值给string类型，printf(%s)会出问题，而用cout不会
		: message_(message) 
	{
		//FillStackTrace();
	}
	explicit Exception(const std::string& message)  //char *类型赋值给string类型，printf(%s)会出问题，而用cout不会
		: message_(message)
	{
		//FillStackTrace();
	}

	virtual ~Exception() throw() {}
	virtual const char * what() const throw(); //throw()代表不会抛出异常，throw(int)代表可能会抛出int类型的异常
	//const char * StackTrace() const throw();

};

class SyntaxError : public Exception
{
public:
	explicit SyntaxError(const char* message)
		: Exception(message) {}

	explicit SyntaxError(const std::string& message)
		: Exception(message) {}

	virtual ~SyntaxError() throw(){}
};

class FileStreamError : public Exception
{
public:
	explicit FileStreamError(const char* message)
		: Exception(message) {}

	explicit FileStreamError(const std::string& message)
		: Exception(message) {}

	virtual ~FileStreamError() throw() {}
};


class DevisorZero : public Exception
{
public:
	explicit DevisorZero(const char* message)
		: Exception(message) {}

	explicit DevisorZero(const std::string& message)
		: Exception(message) {}

	virtual ~DevisorZero() throw() {}
};


class VersionUnMatch : public Exception
{
public:
	explicit VersionUnMatch(const char* message)
		: Exception(message) {}

	explicit VersionUnMatch(const std::string& message)
		: Exception(message) {}

	virtual ~VersionUnMatch() throw() {}
};

#endif //_EXCEPTION_H_
