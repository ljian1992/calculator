#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

#include "Parser.h"

class Scanner;   /*声明Scanner类而不是包含头文件头文件大小会小一点*/
class Calc;

class CommandParser
{
private:
	enum ECommand
	{
		CMD_HELP,
		CMD_QUIT,
		CMD_VAR,
		CMD_FUN,
		CMD_LOAD,
		CMD_SAVE,
		CMD_ERROR,
	};
private:
	Scanner& scanner_;
	Calc &calc_;
	ECommand cmd_;                           //解析到的命令
	std::string cmdName_;                    //命令名

	void Help() const;                       //帮助命令
	void ListVar() const;                    //打印出变量表
	void ListFun() const;                    //打印出函数表
	STATUS Load(const std::string& fileName);//从文件中加载内容到变量表和函数表中
	STATUS Save(const std::string& fileName);//存储变量表和函数表到文件中

public:
	CommandParser(Scanner& scanner, Calc& calc_);   /*与scanner类相关联*/
	STATUS Execute();                         //根据解析到的命令执行命令   
 
};

#endif //_COMMAND_PARSER_H_

