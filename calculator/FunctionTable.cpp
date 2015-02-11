#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include "SymbolTable.h"
#include "FunctionTable.h"
#include "DebugNew.h"

struct FunctionEntry
{
	PtrFun pFun_;
	char * funName_;
};

FunctionEntry Entrys[] =
{
	log,   "log",
	log10, "log10",
	exp,   "exp",
	sqrt,  "sqrt",
	sin,   "sin",
	cos,   "cos",
	tan,   "tan",
	sinh,  "sinh",
	cosh,  "cosh",
	tanh,  "tanh",
	asin,  "asin",
	acos,  "acos",
	atan,  "atan",
};

FunctionTable::FunctionTable(SymbolTable& tbl)
{
	Init(tbl);
}

void FunctionTable::Init(SymbolTable& tbl)
{

	for (unsigned int i = 0; i < sizeof(Entrys) / sizeof(*Entrys); ++i)
	{
		//pFuns_[i] = Entrys[i].pFun_;
		//pFuns_.push_back(Entrys[i].pFun_);
		funsMap_[i] = Entrys[i].pFun_;
		unsigned int id = tbl.Add(Entrys[i].funName_);
		assert(i == id); //函数表最先添加到符号表中符i == id
	}
}

PtrFun FunctionTable::GetFunction(unsigned int id) const
{
	PtrFun pFun = NULL;
	bool IsFouned = false;

	if (id < funsMap_.size())
	{
		//pFun = funsMap_.find();
		std::map<unsigned int, PtrFun>::const_iterator it = funsMap_.find(id);

		if (funsMap_.end() != it)
		{
			pFun = it->second;
			IsFouned = true;
		}
		
	}

	if (IsFouned)
	{
		std::cout << "didn't fouded functions: " << std::endl;
	}
	
	return pFun;
}

unsigned int FunctionTable::GetSize() const
{
	return  funsMap_.size();
}

FunctionTable::~FunctionTable()
{
	//delete[] pFuns_;
}

