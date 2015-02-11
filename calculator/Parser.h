/*********************************************************************************
*FileName: Parser.h
*Author :  Ljian
*Version : 1.0
*Date :  2015年2月8日14:21:59
*Description :
主要功能：定义解析类
相关类：Scanner类
表达式的BNF表示法
	Expr ::= Term{('+' | '-') Term }                    ---->multipleNode
	Expr ::= Term = Expr                                ---->AssignNode

	Term ::= Factor {('*' | '/') Factor }               ---->multipleNode

	Factor ::=
	1.Number                                            ---->NumberNode
	2.Identifier
		2.1.Function                                    ---->FunctionNode
		2.2.Variable                                    ---->VariableNode
	3.'-'Factor                                         ---->UMinusNode
	4.'('Expr ')'
**********************************************************************************/


#ifndef _PARSER_H_
#define _PARSER_H_

#include <memory>

class Scanner;   /*声明Scanner类而不是包含头文件头文件大小会小一点*/
class Node;
class Calc;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT,
};


class Parser
{
private:
	Scanner& scanner_;                   //由于是引用Parser类不负责scanner_的生命周期，若不是引用则为组合关系
	//std::string expression_;
	std::auto_ptr<Node> tree_;           //表达式语法树
	STATUS status_;                      //状态
	Calc& calc_;                         //要处理的符号信息

public:
	Parser(Scanner& scanner, Calc& calc);   /*与scanner类相关联*/
	~Parser();
	STATUS Parse();				            //解析一个表达式生成表达式树
	std::auto_ptr<Node> Expr();				//解析表达式
	std::auto_ptr<Node> Term();				//解析项
	std::auto_ptr<Node> Factor();		    //解析因子
	//std::string& GetExpression_();
	double Calculate() const;              //计算出表达式的值

};

#endif //_PARSER_H_

