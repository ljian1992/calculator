#include <cmath>
#include <cassert>
#include <iostream>
#include "SymbolTable.h"
#include "Storage.h"
#include "Exception.h"

Storage::Storage(SymbolTable & tbl) 
{
	AddConstants(tbl);
}

void Storage::Clear()
{
	cells_.clear();

}


void Storage::AddConstants(SymbolTable & tbl)
{
	unsigned int id = tbl.Add("e");
	AddValue(id, exp(1.0));

	id = tbl.Add("pi");
	AddValue(id, 2.0*acos(0.0));          //pi = 2 * acos (0)
}

double Storage::GetValue(unsigned int id) const
{
	std::map<unsigned int, double>::const_iterator it = cells_.find(id);

	assert(cells_.end() != it);

	return it->second;
}

unsigned int Storage::GetSize() const
{
	return cells_.size();
}

void Storage::SetValue(unsigned int id, double val)
{

	std::map<unsigned int, double>::iterator it = cells_.find(id);
	
	if (cells_.end() != it) //修改值
	{
		cells_[id] = val;
	}
	else  //添加值
	{
		AddValue(id, val);
	}

}


void Storage::AddValue(unsigned int id, double val) 
{ 
	cells_[id] = val; 
}



void Storage::Serialize(Serializer& out) const
{
	out << cells_.size();
	
	std::map<unsigned int, double>::const_iterator it;

	for (it = cells_.begin(); it != cells_.end(); ++it)
	{
		out << it->first << it->second;
	}
}
void Storage::DeSerialize(DeSerializer& in)
{
	Clear();

	unsigned int size;
	in >> size;

	for (unsigned int i = 0; i < size; ++i)
	{
		unsigned int iTmp;
		double dTmp;
		
		in >> iTmp >> dTmp;
		cells_[iTmp] = dTmp;
	}
}
