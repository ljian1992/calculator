/*********************************************************************************
*FileName: Scanner.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:21:59
*Description : 
主要功能：定义扫描类，从标准输入流中扫描表达式相关的符号
**********************************************************************************/

#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>


enum EToken {
	TOKEN_COMMAND,
	TOKEN_ERROR,                 
	TOKEN_END,					 
	TOKEN_NUMBER,				
	TOKEN_IDENTIFIER,			 
	TOKEN_PLUS,				
	TOKEN_MINUS, 
	TOKEN_MUTIPLY,
	TOKEN_DIVIDE, 
	TOKEN_LPARENTHESIS, 
	TOKEN_RPARENTHESIS,
	TOKEN_ASSIGN,
};

class Scanner
{
private:
	std::istream& in_;                 //标准输入流
	bool isEmpty_;                     //是否为空
	EToken token_;                     //记录扫描结果
	double number_;                    //扫描到的数字
	std::string symbol_;               //扫描到标识符
	int look_;                         //扫描到的字符
	void ReadChar();                   //从标准输入流中读取字符

public:
	explicit Scanner(std::istream& in);
	void Accept();                     //扫描一个标识符or操作数or操作数
	void AcceptCommand();              //扫描命令
	void CleanIstream();               //清除标准输入流缓存
	double Number() const;             //获取扫描到的数字
	bool IsEmpty()const;               //判断是否为空
	bool IsDone() const;               //判断是否扫描完毕
	bool IsCommand() const;            //判断是否是命令
	std::string GetSymbol() const;     //获取扫描到的标识符
	EToken Token() const;              //获取扫描结果
	
};

#endif //_SANNER_H_
