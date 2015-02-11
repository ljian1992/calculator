/*********************************************************************************
*FileName: SymbolTable.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:19:43
*Description :
主要功能：定义符号表类，用于与表达式计算相关的符号
**********************************************************************************/
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <string>
#include <map>
#include "Serial.h"

class SymbolTable : public Serializable
{
private:
	std::map<const std::string, unsigned int> dictionary_;  //存储符号与id相对应得关系
	unsigned int curId_;                                    //存储将要加入符号表的符号id
public:
	enum { IDNOTFOUND = 0xFFFFFFFF };                       //IDNOTFOUND代表在符号表中找不到相应的符号
	SymbolTable() : curId_(0) {}                            
	unsigned int Add(const std::string& str);               //向符号表中加入符号
	unsigned int Find(const std::string& str) const;        //根据符号寻找符号表中是否存储该符号
	unsigned int GetCurId()const;                           //获取下一个的加入符号表的符号id
	void Clear();                                           //清楚符号表
	const std::string &GetSymbolName(unsigned int id) const;//根据id查找并获取符号表中的符号

	virtual void Serialize(Serializer& out) const;          //将符号表中的内容存储到文件中
	virtual void DeSerialize(DeSerializer& in);             //将文件中的内容加载到符号表中
};

#endif  //_SYMBOLTABLE_H_

