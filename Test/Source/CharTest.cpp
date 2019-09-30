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
	TEST_CLASS(CharTest)
	{
	public:
		TEST_METHOD(AnyTest)
		{
			char chars[] = "A";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Char::Any<char> rule;

			// Consume one char and reach the context end
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
		}
		TEST_METHOD(ExpectTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Char::Expect<char> rule('A');

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Can't consume next character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
		}
		TEST_METHOD(ChoiceTest)
		{
			char chars[] = "BCAD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Char::Choice<char> rule({ 'A', 'B', 'C' });

			// Consume character 'B'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Consume character 'C'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Consume character 'A'
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
		TEST_METHOD(RangeTest)
		{
			char chars[] = "BCAD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Char::Range<char> rule('A', 'C');

			// Consume character 'B'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Consume character 'C'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Consume character 'A'
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
			Char::Digit<char> rule;

			// Consume digits
			for (unsigned i = 0; i < 10; ++i) {
				Assert::IsTrue(rule.consume(context));
			}
			Assert::AreEqual(10U, context.getOffset());

			// Can't consume next character 'a'
			Assert::IsFalse(rule.consume(context));
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
			Char::LowerAZ<char> rule;

			// Consume alphabet
			for (unsigned i = 0; i < 26; ++i) {
				Assert::IsTrue(rule.consume(context));
			}
			Assert::AreEqual(26U, context.getOffset());

			// Can't consume next character '0'
			Assert::IsFalse(rule.consume(context));
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
			Char::UpperAZ<char> rule;

			// Consume alphabet
			for (unsigned i = 0; i < 26; ++i) {
				Assert::IsTrue(rule.consume(context));
			}
			Assert::AreEqual(26U, context.getOffset());

			// Can't consume next character 'a'
			Assert::IsFalse(rule.consume(context));
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
			Char::AnyAZ<char> rule;

			// Consume alphabet
			for (unsigned i = 0; i < 52; ++i) {
				Assert::IsTrue(rule.consume(context));
			}
			Assert::AreEqual(52U, context.getOffset());

			// Can't consume next character '0'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(52U, context.getOffset());

			// Skip character '0' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(53U, context.getOffset());
		}
	};
}
