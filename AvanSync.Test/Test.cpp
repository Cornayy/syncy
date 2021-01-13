#include "pch.h"
#include "CppUnitTest.h"
#include <asio/ip/tcp.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AvanSyncTest
{
	TEST_CLASS(AvanSyncTest)
	{
	public:
		const char* LF = "\n";
		const char* CRLF = "\r\n";

		TEST_METHOD(WELCOME)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string welcome;

			std::getline(stream, welcome);
			welcome.erase(welcome.end() - 1);
			
			Assert::AreEqual("Welcome to AvanSync server 1.0", welcome.c_str());
		}
		
		TEST_METHOD(INFO)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;
			
			std::getline(stream, response);
			stream << "info" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);

			Assert::AreEqual("AvanSync server 1.0, copyright (c) 2021 Corne Eggebeen.", response.c_str());
		}

		TEST_METHOD(MKDIR)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;

			std::getline(stream, response);
			stream << "mkdir" << CRLF;
			stream << "./" << CRLF;
			stream << "test" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);

			Assert::AreEqual("OK", response.c_str());
		}

		TEST_METHOD(DIR)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;

			std::getline(stream, response);
			stream << "mkdir" << CRLF;
			stream << "./" << CRLF;
			stream << "test" << CRLF;
			std::getline(stream, response);
			stream << "dir" << CRLF;
			stream << "./test" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);

			Assert::AreEqual("0", response.c_str());
		}

		TEST_METHOD(REN)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;
			std::string deletion;

			std::getline(stream, response);
			stream << "mkdir" << CRLF;
			stream << "./" << CRLF;
			stream << "test" << CRLF;
			std::getline(stream, response);
			stream << "ren" << CRLF;
			stream << "./test" << CRLF;
			stream << "./testrenamed" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);
			stream << "del" << CRLF;
			stream << "./testrenamed" << CRLF;
			std::getline(stream, deletion);
			deletion.erase(deletion.end() - 1);

			Assert::AreEqual("OK", response.c_str());
			Assert::AreEqual("OK", deletion.c_str());
		}

		TEST_METHOD(DEL)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;

			std::getline(stream, response);
			stream << "mkdir" << CRLF;
			stream << "./" << CRLF;
			stream << "test" << CRLF;
			std::getline(stream, response);
			stream << "del" << CRLF;
			stream << "./test" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);

			Assert::AreEqual("OK", response.c_str());
		}

		TEST_METHOD(QUIT)
		{
			asio::ip::tcp::iostream stream{ "localhost", "3000" };
			std::string response;

			std::getline(stream, response);
			stream << "quit" << CRLF;
			std::getline(stream, response);
			response.erase(response.end() - 1);

			Assert::AreEqual("Bye.", response.c_str());
		}
	};
}
