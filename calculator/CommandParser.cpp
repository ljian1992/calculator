#include <cassert>
#include <iostream>
#include "CommandParser.h"
#include  "scanner.h"
#include "Calc.h"
#include "Exception.h"
#include "Serial.h"

void CommandParser::Help() const
{
	std::cout << "----------------------Recognized commands----------------------" << std::endl;
	std::cout << "!help" << std::endl;
	std::cout << "!quit" << std::endl;
	std::cout << "!v" << std::endl;
	std::cout << "!f" << std::endl;
	std::cout << "!load filename" << std::endl;
	std::cout << "!save filename" << std::endl;

}

void CommandParser::ListVar() const
{
	std::cout << "----------------------Variable List----------------------" << std::endl;
	calc_.ListVariable();
	std::cout <<std::endl<< "----------------------Variable List----------------------" << std::endl;
}

void CommandParser::ListFun() const
{
	std::cout << "----------------------Function List----------------------" << std::endl;
	calc_.ListFun();
	std::cout << std::endl << "----------------------Function List----------------------"  << std::endl;
}


const long VERSION = 1;

STATUS CommandParser::Load(const std::string& fileName)
{
	std::cout << "load " << fileName << std::endl;

	STATUS status = STATUS_OK;
	try
	{
		DeSerializer in (fileName);
		long version;
		in >> version;      //版本号

		if (VERSION != version)
		{
			throw VersionUnMatch("unmatch version!");
		}
		calc_.DeSerialize(in);
	}
	catch (VersionUnMatch& e)
	{
		std::cout << "Load Error: " << e.what() << std::endl;
		status = STATUS_ERROR;
	}
	catch (Exception& e)
	{
		std::cout << "Load Error: " << e.what() << std::endl;
		status = STATUS_ERROR;
	}
	

	return status;
}



STATUS CommandParser::Save(const std::string& fileName)
{
	std::cout << "save " << fileName << std::endl;

	STATUS status = STATUS_OK;
	try
	{
		Serializer out(fileName);

		out << VERSION;      //版本号
		calc_.Serialize(out);
	}
	catch (FileStreamError& e)
	{
		std::cout << "Save Error: " << e.what() << std::endl;
		status = STATUS_ERROR;
	}

	return status;
}

CommandParser::CommandParser(Scanner & scanner, Calc & calc)
	: scanner_(scanner), calc_(calc)
{
	assert (scanner_.IsCommand());
	scanner_.Accept();
    cmdName_ = scanner_.GetSymbol();


	//需要修改成表驱动	
	switch (cmdName_[0])
	{
	case 'h':
	case 'H':
		cmd_ = CMD_HELP;
		break;
	case 'q':
	case 'Q':
		cmd_ = CMD_QUIT;
		break;
	case 'v':
	case 'V':
		cmd_ = CMD_VAR;
		break;
	case 'f':
	case 'F':
		cmd_ = CMD_FUN;
		break;
	case 'l':
	case 'L':
		cmd_ = CMD_LOAD;
		break;
	case 's':
	case 'S':
		cmd_ = CMD_SAVE;
		break;
	default:
		break;
	}
}

STATUS CommandParser::Execute()
{
	STATUS status = STATUS_OK;
	scanner_.AcceptCommand();
	std::string fileName;

	switch (cmd_)
	{
	case CMD_HELP:
		Help();
		break;

	case CMD_QUIT:
		std::cout << "Quit" << std::endl;
		status = STATUS_QUIT;
		break;

	case CMD_VAR:
		ListVar();
		break;

	case CMD_FUN:
		ListFun();
		break;

	case CMD_LOAD:
		fileName = scanner_.GetSymbol();
		status = Load(fileName);
		break;

	case CMD_SAVE:
		fileName = scanner_.GetSymbol();
		status = Save(fileName);
		break;

	default:
		std::cout << "Unknown command:" << cmdName_ << std::endl;
		status = STATUS_ERROR;
		break;
	}
 
	return status;
}


