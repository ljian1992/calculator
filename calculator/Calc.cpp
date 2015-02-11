#include <iostream>
#include <iomanip>
#include "Calc.h"

unsigned int Calc::FindSymbol(const std::string & str) const
{
	return symTbl_.Find(str);
}

unsigned int Calc::AddSymbol(const std::string & str)
{
	return symTbl_.Add(str);
}


Storage & Calc::GetStorage() 
{
	return storage_;
}

bool Calc::IsFunction(unsigned int id) const
{
	return (id < functionTbl_.GetSize());  //函数最先添加到符号表故id小于函数表中总的个数，就是在函数表当中
}

PtrFun Calc::GetFunction(unsigned int id) const
{
	return functionTbl_.GetFunction (id);
}

double Calc::GetVariableValue(unsigned int id) const
{

	return storage_.GetValue(id);
}

void Calc::ListFun() const
{
	for (unsigned int i = 0; i < functionTbl_.GetSize(); ++i)
	{
		std::cout << std::left << std::setw(10) << symTbl_.GetSymbolName(i);
		if (i>0 && 0 == i % 5 )
		{
			std::cout << std::endl;
		}
	}
}

void Calc::ListVariable() const
{
	for (unsigned int i = functionTbl_.GetSize(); i < symTbl_.GetCurId(); ++i)
	{
		std::string name = symTbl_.GetSymbolName(i);
		double value = GetVariableValue(i);

		std::cout << std::left << name << " = " << value << std::endl;
	}
}

void Calc::Serialize(Serializer& out) const
{
	symTbl_.Serialize(out);
	storage_.Serialize(out);
}

void Calc::DeSerialize(DeSerializer& in)
{
	symTbl_.DeSerialize(in);
	storage_.DeSerialize(in);
}