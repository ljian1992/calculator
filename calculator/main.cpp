#include <iostream>
#include <string>
#include "Scanner.h"
#include "Parser.h"
#include "calc.h"
#include "Exception.h"
#include "CommandParser.h"

using namespace std;

int main(void)
{
	STATUS status = STATUS_OK;
	Calc calc;
	do
	{
		std::cout << ">>";
	
		Scanner scanner(std::cin);

		if (!scanner.IsEmpty())
		{
			if (scanner.IsCommand())
			{
				CommandParser parser(scanner, calc);
				status = parser.Execute();

			}
			else
			{
				Parser parser(scanner, calc);
				try
				{
					status = parser.Parse();
					if (STATUS_OK == status)
					{
						std::cout << parser.Calculate() << endl;
					}
					else
					{
						std::cout << "Syntax error!" << endl;
					}
				}
				catch (SyntaxError& se)
				{
					//status = STATUS_QUIT;
					std::cout << se.what() << std::endl;
					//std::cout << se.StatTrace() << std::endl;
				}

				catch (Exception& e)
				{
					//status = STATUS_QUIT;
					std::cout << e.what() << std::endl;
					//std::cout << e.StatTrace() << std::endl;
				}
				catch (std::bad_alloc& e)
				{
					//status = STATUS_QUIT;
					std::cout << e.what() << std::endl;
				}
				catch (...)
				{
					//status = STATUS_QUIT;
					std::cout << "Internal error!" << std::endl;
				}

			}
	
		}
		else
		{
			std::cout << "Expression is empty!" << endl;
		}

		scanner.CleanIstream(); //清空标准输入缓存
		
	} while (status != STATUS_QUIT);

	return 0;
}