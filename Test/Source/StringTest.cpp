// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#include "CppUnitTest.h"

#include "../../Library/Source/Proyth.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Proyth;
using namespace Proyth::Rules;

namespace ProythTest
{
	TEST_CLASS(StringTest)
	{
	public:
		TEST_METHOD(ExpectTest)
		{
			char chars[] = "ABCABD";
			char string[] = "ABC";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::Expect<char> rule(string);

			// Consume characters 'ABC'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume next characters 'ABD'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip characters 'ABD' and reach the context end
			context.forward(3);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(6U, context.getOffset());
		}
		TEST_METHOD(ChoiceTest)
		{
			char chars[] = "ABDABCABEACB";
			char option1[] = "ABC";
			char option2[] = "ABD";
			char option3[] = "ABE";
			Strings::View<char> options[] = { option1, option2, option3 };
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::Choice<char> rule(options);

			// Consume characters 'ABD'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Consume characters 'ABC'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(6U, context.getOffset());

			// Consume characters 'ABE'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(9U, context.getOffset());

			// Can't consume next characters 'ACB'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(9U, context.getOffset());

			// Skip characters 'ACB' and reach the context end
			context.forward(3);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(12U, context.getOffset());
		}
		TEST_METHOD(RangeTest)
		{
			char chars[] = "BCAD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::Range<char> rule('A', 'C');

			// Consume characters 'BCA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume next character 'D'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip character 'D' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(4U, context.getOffset());
		}
		TEST_METHOD(DigitTest)
		{
			char chars[] = "0123456789a";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::Digit<char> rule;

			// Consume all digits
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(10U, context.getOffset());

			// Skip character 'a' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(11U, context.getOffset());
		}
		TEST_METHOD(LowerAZTest)
		{
			char chars[] = "abcdefghijklmnopqrstuvwxyz0";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::LowerAZ<char> rule;

			// Consume alphabet
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(26U, context.getOffset());

			// Skip character '0' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(27U, context.getOffset());
		}
		TEST_METHOD(UpperAZTest)
		{
			char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZa";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::UpperAZ<char> rule;

			// Consume alphabet
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(26U, context.getOffset());

			// Skip character 'a' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(27U, context.getOffset());
		}
		TEST_METHOD(AnyAZTest)
		{
			char chars[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			String::AnyAZ<char> rule;

			// Consume alphabet
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(52U, context.getOffset());

			// Skip character '0' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(53U, context.getOffset());
		}
	};
}
