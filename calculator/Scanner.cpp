#include <cctype>
#include <cstdio>
#include <iostream>
#include "Scanner.h"



void Scanner::ReadChar()
{
	look_ = in_.get();
	while (' ' == look_ || '\t' == look_)
	{
		look_ = in_.get();
	}

}

Scanner::Scanner(std::istream& in) : in_(in)
{
	Accept();
	isEmpty_ = (TOKEN_END == token_);
}

void Scanner::Accept()
{
	ReadChar();
	switch (look_)
	{
	case '!':
		token_ = TOKEN_COMMAND;
		break;
	case '+':
		token_ = TOKEN_PLUS;
		break;

	case '-':
		token_ = TOKEN_MINUS;
		break;

	case '*':
		token_ = TOKEN_MUTIPLY;
		break;

	case '/':
		token_ = TOKEN_DIVIDE;
		break;

	case '=':
		token_ = TOKEN_ASSIGN;
		break;

	case '(':
		token_ = TOKEN_LPARENTHESIS;
		break;

	case ')':
		token_ = TOKEN_RPARENTHESIS;
		break;

	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
		in_.putback(look_);
		in_ >> number_;
		token_ = TOKEN_NUMBER;
		break;


	case '\0': case '\n':  case 'r': case EOF:  /*结束标志*/
		token_ = TOKEN_END;
		break;

	default:
		if ( isalpha(look_) || '_' == look_ )
		{
			token_ = TOKEN_IDENTIFIER;
			symbol_.erase();
			do
			{
				symbol_ += look_;
				look_ = in_.get();
			} while (isalnum(look_) || '_' == look_);
			in_.putback(look_); //归还多获取到的字符

		}
		else
		{
			token_ = TOKEN_ERROR;
		}
		break;

	}
}



void Scanner::AcceptCommand()
{
	ReadChar();
	symbol_.erase();
	while (!isspace(look_))
	{
		symbol_ += look_;
		look_ = in_.get();
	}

}

void Scanner::CleanIstream()
{
	in_.clear();
	in_.sync();
}

double Scanner::Number() const
{
	return number_;
}

bool Scanner::IsEmpty() const
{
	return isEmpty_;
}

bool Scanner::IsDone() const
{
	return (TOKEN_END == token_);
}

bool Scanner::IsCommand() const
{
	return (TOKEN_COMMAND == token_);
}

std::string Scanner::GetSymbol() const
{
	return symbol_;
}

EToken Scanner::Token() const
{
	return token_;
}
