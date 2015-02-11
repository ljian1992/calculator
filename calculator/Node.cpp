#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include "Node.h"
#include "Storage.h"
#include "DebugNew.h"
#include "Exception.h"

using namespace std;

double NumberNode::Calc() const
{
	return number_;
}


BinaryNode::~BinaryNode() {}


double AddNode::Calc() const
{
	return left_->Calc() + right_->Calc();
}

double SubNode::Calc() const
{
	return left_->Calc() - right_->Calc();
}

double MultiplyNode::Calc() const
{
	return left_->Calc() * right_->Calc();
}


double DivideNode::Calc() const
{
	double divisor = right_->Calc();

	if (!(0-0.0000001 <= divisor && divisor <= 0+0.0000001))
	{
		return left_->Calc() / divisor;
	}
	else
	{
		throw DevisorZero("Divisor is zero!");
		return HUGE_VAL;
	}

}


UnaryNode::~UnaryNode() {}

double FunctionNode::Calc() const
{
	return (*pFun_)(child_->Calc());
}

double UMinusNode::Calc() const
{
	return -child_->Calc();
}


MultipleNode::MultipleNode(std::auto_ptr<Node>& node)
{
	AppendChild(node, true);    //-4+5-4--->由于有了UnaryNode来处理故第一节点是都是正的
}

void MultipleNode::AppendChild(std::auto_ptr<Node>& node, bool positive)
{
	childs_.push_back(node.release());
	positives_.push_back(positive);
}

MultipleNode::~MultipleNode()
{
	std::vector<Node *>::const_iterator it;
	for (it = childs_.begin(); it != childs_.end(); ++it)
	{
		delete *it;
	}
}


double SumNode::Calc() const
{
	double sum = 0.0;
	std::vector<Node *>::const_iterator childIt = childs_.begin();
	std::vector<bool>::const_iterator positiveIt = positives_.begin();

	for (; childIt != childs_.end(); ++childIt, positiveIt++)
	{
		assert(positiveIt != positives_.end());  /*假设positiveIt != positives_.end()*/
		double val = (*childIt)->Calc();
		if (*positiveIt)
		{
			sum += val;
		}
		else
		{
			sum -= val;
		}
		
	}
	assert(positiveIt == positives_.end());  /*假设positiveIt == positives_.end()*/
	
	return sum;
}


double ProductNode::Calc() const
{
	double ret = 1.0;
	std::vector<Node *>::const_iterator childIt = childs_.begin();
	std::vector<bool>::const_iterator positiveIt = positives_.begin();

	for (; childIt != childs_.end(); ++childIt, positiveIt++)
	{
		assert(positiveIt != positives_.end());  /*假设positiveIt != positives_.end()*/
		double val = (*childIt)->Calc();

		if (*positiveIt)
		{
			ret *= val;
		}
		else if (!(0 - 0.0000001 <= val && val <= 0 + 0.0000001))  
		{
			ret /= val;
		}
		else
		{
			throw DevisorZero("Divisor is zero!");
			ret = HUGE_VAL;
		}

	}
	assert(positiveIt == positives_.end());  /*假设positiveIt == positives_.end()*/

	return ret;
}



double VariableNode::Calc() const
{
	return storage_.GetValue(id_);
}

bool VariableNode::IsLvalue() const
{
	return true;
}

void VariableNode::Assign(double val)
{
	storage_.SetValue(id_, val);
}


double AssignNode::Calc() const
{
	double x = 0.0;

	x = right_->Calc();
	left_->Assign(x);
	
	return x;
}