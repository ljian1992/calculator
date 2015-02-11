/*********************************************************************************
*FileName: Storage.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:17:11
*Description :
主要功能：定义了存储变量类
相关关联的类：SymbolTable
**********************************************************************************/
#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include <map>
#include "Serial.h"

class SymbolTable;

class Storage : public Serializable
{
private:
	std::map<unsigned int, double> cells_;  //存储符号表中id与值多对应的关系

public:
	Storage(SymbolTable& tbl);
	void Clear();                                 //清除数据
	void AddConstants(SymbolTable& tbl);          //增加常量，目前只支持pi e
	double GetValue(unsigned int id) const;       //根据id获得想对于的值
	unsigned int GetSize() const;                 //获取map中有多少个数据
	void SetValue(unsigned int id, double val);   //设置map中的值
	//void Storage::AddValue(unsigned int id, double val，bool isInit);   //想map中添加值
	void AddValue(unsigned int id, double val);
	virtual void Serialize(Serializer& out) const;//将Storage类中的值存入文件存储
	virtual void DeSerialize(DeSerializer& in);   //将文件中的值加载到Storage类中
};

#endif //_STORAGE_H_