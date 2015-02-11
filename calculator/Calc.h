#ifndef _CALC_H_
#define _CALC_H_

#include <string>
#include "SymbolTable.h"
#include "FunctionTable.h"
#include "Storage.h"
#include "Serial.h"


class Parser;

class Calc : public Serializable
{
	friend class Parser;  //使到Parser类方便的访问Calc的私有成员
private:
	//-->由于定义了SymbolTable类，因此需要把它的头文件包含起来， Calc类负责symTbl_的生命周期，因此是两种之间是组合关系,
	//由于Storage的构造函数需要用到SymbolTable的引用，故声明顺序SymbolTable在Storage的前面
	SymbolTable symTbl_;  
	FunctionTable functionTbl_;   //由于函数表中的函数是固定的，因此把函数表的构造放在符号表的前面
	Storage storage_;             //变量的个数是不固定的
	unsigned int FindSymbol(const std::string& str) const;  //在符号表中查找str符号
	unsigned int AddSymbol(const std::string& str);         //往符号表中添加符号
	Storage& GetStorage();                                  //获取stroage_的引用
	bool IsFunction(unsigned int id) const;                 //判断是否是函数
	PtrFun GetFunction(unsigned int id) const;              //获取函数指针
	double GetVariableValue(unsigned int id) const;         //获取变量的值
public:
	Calc() : symTbl_(), functionTbl_(symTbl_), storage_(symTbl_) {}
	void ListFun() const;                                   //打印函数表
	void ListVariable() const;                              //打印变量表

	virtual void Serialize(Serializer& out) const;          //将函数表和变量表中的内容存储到文件中
	virtual void DeSerialize(DeSerializer& in);             //从文件中加载内容到符号表和变量表中

};
#endif //_CALC_H_

