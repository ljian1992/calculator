/*********************************************************************************
*FileName: Node.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:21:26
*Description :
主要功能：定义函数表类
相关关联的类：SymbolTable
**********************************************************************************/

#ifndef _FUNCTIONTABLE_H_
#define _FUNCTIONTABLE_H_

#include <vector>
#include <map>

class SymbolTable;

typedef double(*PtrFun)(double);  //重命名了一种函数指针类

class FunctionTable
{
private:                
	std::map<unsigned int, PtrFun> funsMap_;     //存储符号表中的id与对应的数学函数指针
public:
	FunctionTable(SymbolTable& tbl);
	void Init(SymbolTable& tbl);                 //存储是函数表
	PtrFun GetFunction(unsigned int id) const;   //根据id获取函数表中对应的函数
	unsigned int GetSize() const;                //获得函数表中有多少个函数
   ~FunctionTable();                             

};

#endif //_FUNCTIONTABLE_H_