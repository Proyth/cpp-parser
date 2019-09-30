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
	TEST_CLASS(FlowTest)
	{
	public:
		TEST_METHOD(AnyTest)
		{
			char chars[] = "BACD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::Any<Char::Expect, Char::Expect, Char::Expect>::Pack<char> rule({ 'A' }, { 'B' }, { 'C' });

			// Consume character 'B'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Consume character 'C'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume character 'D'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip character 'D' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(4U, context.getOffset());
		}
		TEST_METHOD(AllTest)
		{
			char chars[] = "ABCD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::All<Char::Expect, Char::Expect, Char::Expect>::Pack<char> rule({ 'A' }, { 'B' }, { 'C' });

			// Consume characters 'ABC'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume character 'D'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip character 'D' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(4U, context.getOffset());
		}
		TEST_METHOD(NotTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::Not<Char::Expect>::Pack<char> rule({ 'A' });

			// Consume character 'A' but returns false.
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(0U, context.getOffset());

			// Skip character 'B'
			context.forward(1);

			// Can't consume character 'B' but returns true
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
		}
		TEST_METHOD(TrueTest)
		{
			char chars[] = "A";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::True<char> rule;

			// Returns true and doen't increase the offset.
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(0U, context.getOffset());
		}
		TEST_METHOD(FalseTest)
		{
			char chars[] = "A";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::False<char> rule;

			// Returns false and doen't increase the offset.
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(0U, context.getOffset());
		}
		TEST_METHOD(RepeatTest)
		{
			char chars[] = "AAAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::Repeat<Char::Expect>::Pack<char> rule('A');

			// Consume all characters 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(4U, context.getOffset());
		}
		TEST_METHOD(ReferenceTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Char::Expect<char> expectRule('A');
			Flow::Reference<Char::Expect>::Pack<char> rule(expectRule);

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
		}
		TEST_METHOD(ConditionTest)
		{
			char chars[] = "ABCD";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::Condition<Char::Expect, Char::Expect, Char::Expect>::Pack<char> rule({ 'A' }, { 'B' }, { 'C' });

			// Consume characters 'A' and 'B'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Can't consume character 'A' but consumes the 'C' one
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Can't consume character 'D' and 'C' neither.
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());

			// Skip character 'D' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(4U, context.getOffset());
		}
		TEST_METHOD(OptionTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::Option<Char::Expect>::Pack<char> rule({ 'A' });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Can't consume character 'B' but still returns true
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
		}
		TEST_METHOD(EndTest)
		{
			char chars[] = "A";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Flow::End<char> rule;

			// Isn't the context end.
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(0U, context.getOffset());

			// Reach the context end.
			context.forward(1);

			// Is the context end.
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
		}
	};
}
