/*********************************************************************************
*FileName: Node.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:17:11
*Description :
主要功能：定义计算节点类
**********************************************************************************/
#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <cassert>
#include  <memory>
#include "FunctionTable.h"


class Storage;

class Noncpyable
{
protected:
	Noncpyable() {}
	~Noncpyable() {}
private:
	Noncpyable(const Noncpyable &) ;
	const Noncpyable& operator= (const Noncpyable &) const;
};
 

class Node  : private Noncpyable  
{
public:
	virtual double Calc() const = 0;
	virtual bool IsLvalue() const
	{
		return false;
	}
	virtual void Assign(double val = 0.0) 
	{
		assert(!"Assign called incorrectlly.");
	}

	virtual ~Node() {};  //抽象类的析构函数要加virtual，这样派生类的析构函数才会被调用
};


class NumberNode : public Node
{
protected:
	const double number_;
public:
	NumberNode(double number) :number_(number) {}
	virtual double Calc() const ; 
};


class BinaryNode : public Node
{
protected:
	std::auto_ptr<Node> left_;
	std::auto_ptr<Node> right_;

public:
	BinaryNode(std::auto_ptr<Node>&  left, std::auto_ptr<Node>& right)
		: left_(left), right_(right) {}

	~BinaryNode();

};

class AddNode : public BinaryNode
{
public:
	AddNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) {}
	virtual double Calc() const;
};

class SubNode : public BinaryNode
{
public:
	SubNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) {}
	virtual double Calc() const;
};

class MultiplyNode : public BinaryNode
{
public:
	MultiplyNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) {}
	virtual double Calc() const;
};

class DivideNode : public BinaryNode
{
public:
	DivideNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) {}
	virtual double Calc() const;
};


class AssignNode : public BinaryNode
{
public:
	AssignNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) 
	{
		assert(left_->IsLvalue());
	} 
	double Calc() const;


};


class UnaryNode : public Node
{
protected:
	std::auto_ptr<Node> child_;
public:
	UnaryNode(std::auto_ptr<Node> &child)
		:child_(child) {};
	~UnaryNode();
};

class FunctionNode : public UnaryNode
{
protected:
	PtrFun pFun_;
public:
	FunctionNode(std::auto_ptr<Node>& child, PtrFun pFun)
		: UnaryNode(child), pFun_(pFun) {}
	double Calc() const;
};

class UMinusNode : public UnaryNode
{
public:
	UMinusNode(std::auto_ptr<Node>& child)
		: UnaryNode(child) {}
	double Calc() const;
};



class MultipleNode : public Node
{
protected:
	std::vector<Node *> childs_;
	std::vector<bool> positives_;

public:
	MultipleNode(std::auto_ptr<Node>& node);
	void AppendChild(std::auto_ptr<Node>& node, bool positive);
	~MultipleNode();
};

class SumNode : public MultipleNode
{
public:
	SumNode(std::auto_ptr<Node>& node) : MultipleNode(node) {}
	double Calc() const;
};

class ProductNode : public MultipleNode
{
public:
	ProductNode(std::auto_ptr<Node>& node) : MultipleNode(node) {}
	double Calc() const;
};


class VariableNode : public Node
{
protected:
	const unsigned int id_;
	Storage& storage_;

public:
	VariableNode(unsigned int id, Storage& storage)
		: id_(id), storage_(storage) {}

	double Calc() const;
	bool IsLvalue() const;
	void Assign(double val);
 };

#endif

