/*********************************************************************************
*FileName: Serial.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:25:20
*Description :
主要功能：定义了序列化类，和反序列化类，以及可序列化接口，用于把内置类型存储到文件中
**********************************************************************************/
#ifndef _SERIAL_H_
#define  _SERIAL_H_

#include <fstream>
#include <string>

class Serializer
{
private:
	std::ofstream stream_;
public:
	Serializer(const std::string& fileName);
	Serializer& Put(int x);
	Serializer& Put(unsigned int x);
	Serializer& Put(long x);
	Serializer& Put(unsigned long x);
	Serializer& Put(double x);
	Serializer& Put(const std::string& x);
	Serializer& Put(bool x);
	

	Serializer& operator<< (int x);
	Serializer& operator<< (unsigned int x);
	Serializer& operator<< (long x);
	Serializer& operator<< (unsigned long x);
	Serializer& operator<< (double x);
	Serializer& operator<< (const std::string& x);
	Serializer& operator<< (bool x);
};

class DeSerializer
{
private:
	std::ifstream stream_;
public:
	DeSerializer(const std::string& fileName);
	DeSerializer& Get(int& x);
	DeSerializer& Get(unsigned int& x);
	DeSerializer& Get(long& x);
	DeSerializer& Get(unsigned long& x);
	DeSerializer& Get (double& x);
	DeSerializer& Get(std::string& x);
	DeSerializer& Get(bool& x);

	DeSerializer& operator>> (int& x);
	DeSerializer& operator>> (unsigned int& x);
	DeSerializer& operator>> (long& x);
	DeSerializer& operator>> (unsigned long& x);
	DeSerializer& operator>> (double& x);
	DeSerializer& operator>> (std::string& x);
	DeSerializer& operator>> (bool& x);
};

class Serializable
{
public:
	virtual void Serialize(Serializer& out) const = 0;
	virtual void DeSerialize(DeSerializer& in) = 0;
};

#endif //_SERIAL_H_

