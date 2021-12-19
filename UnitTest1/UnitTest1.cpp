#include "pch.h"
#include "CppUnitTest.h"
#include "..//Calculator.h"
#include "..//String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCalculator
{
	TEST_CLASS(UnitTestCalculator)
	{
	public:

		TEST_METHOD(Test_String) {
			String str;
			str = "test";
			Assert::IsTrue(str.function_length() == 4);
			Assert::IsTrue(str.empty() == 1);
			Assert::IsTrue(str.last_simv(str) == 't');
			str.pop_last_simv();
			Assert::IsTrue(str.last_simv(str) == 's');
		}
		TEST_METHOD(Test_Couting) {
			char plus = '+', multi = '.', unar_m = 126;
			char seven = '7', dot = '.', five = '5', minus = '-';
			String str_num;
			str_num = "15 2.5 ";
			Culculate(plus, str_num);
			Assert::IsTrue(str_num[1] == seven);
			Assert::IsTrue(str_num[2] == dot);
			Assert::IsTrue(str_num[3] == five);

			String str_num2;
			str_num2 = "2 2.5 ";
			Culculate(multi, str_num2);
			Assert::IsTrue(str_num2[0] == five);

			String str_num3;
			str_num3 = "5 ";
			Culculate(unar_m, str_num3);
			Assert::IsTrue(str_num3[0] == minus);
			Assert::IsTrue(str_num3[1] == five);
		}
		TEST_METHOD(Test_Posfix) {
			String str;
			char six = '6', nine = '9', eight = '8', one = '1', minus = '-', multi = '*', plus = '+', degree = '^';
			str = "9-8*1+6^8";
			Postfix_notation_and_Calculation(str);
			Assert::IsTrue(str[0] == nine);
			Assert::IsTrue(str[2] == eight);
			Assert::IsTrue(str[4] == one);
			Assert::IsTrue(str[6] == multi);
			Assert::IsTrue(str[8] == minus);
			Assert::IsTrue(str[10] == six);
			Assert::IsTrue(str[12] == eight);
			Assert::IsTrue(str[14] == degree);
			Assert::IsTrue(str[16] == plus);
		}
	};
}