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
	TEST_CLASS(DataTest)
	{
	public:
		TEST_METHOD(LeftNodeTest)
		{
			char chars[] = "AAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Node<Char::Expect>::Pack<char> rule(0xA0, Node<char>::Direction::Left, { 'A' });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree->getLeft());
			Assert::AreEqual(0x0A0, tree->getLeft()->getType());
			Assert::AreEqual(1U, tree->getLeft()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());
		}
		TEST_METHOD(RightNodeTest)
		{
			char chars[] = "AAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Node<Char::Expect>::Pack<char> rule(0xA0, Node<char>::Direction::Right, { 'A' });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree->getRight());
			Assert::AreEqual(0x0A0, tree->getRight()->getType());
			Assert::AreEqual(1U, tree->getRight()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());
		}
		TEST_METHOD(DownNodeTest)
		{
			char chars[] = "AAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Node<Char::Expect>::Pack<char> rule(0xA0, Node<char>::Direction::Down, { 'A' });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree->getDown());
			Assert::AreEqual(0x0A0, tree->getDown()->getType());
			Assert::AreEqual(1U, tree->getDown()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());
		}
		TEST_METHOD(LeftTreeTest)
		{
			char chars[] = "AABAAC";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);

			Data::Tree<Flow::Repeat<Data::Node<Char::Expect>::Pack>::Pack>::Pack<char>
				rule(Node<char>::Direction::Left, { { 0xA0, Node<char>::Direction::Right, { 'A' } } });

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());
			Assert::IsNotNull(tree->getRight());
			Assert::AreEqual(0x0A0, tree->getRight()->getType());
			Assert::AreEqual(1U, tree->getRight()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B'
			context.forward(1);

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(5U, context.getOffset());
			Assert::IsNotNull(tree->getLeft());
			Assert::AreEqual(0x0A0, tree->getLeft()->getType());
			Assert::AreEqual(3U, tree->getLeft()->getOffset());
			Assert::IsNotNull(tree->getLeft()->getRight());
			Assert::AreEqual(0x0A0, tree->getLeft()->getRight()->getType());
			Assert::AreEqual(4U, tree->getLeft()->getRight()->getOffset());

			// Skip character 'C' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(6U, context.getOffset());
		}
		TEST_METHOD(RightTreeTest)
		{
			char chars[] = "AABAAC";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);

			Data::Tree<Flow::Repeat<Data::Node<Char::Expect>::Pack>::Pack>::Pack<char>
				rule(Node<char>::Direction::Right, { { 0xA0, Node<char>::Direction::Down, { 'A' } } });

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());
			Assert::IsNotNull(tree->getDown());
			Assert::AreEqual(0x0A0, tree->getDown()->getType());
			Assert::AreEqual(1U, tree->getDown()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B'
			context.forward(1);

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(5U, context.getOffset());
			Assert::IsNotNull(tree->getRight());
			Assert::AreEqual(0x0A0, tree->getRight()->getType());
			Assert::AreEqual(3U, tree->getRight()->getOffset());
			Assert::IsNotNull(tree->getRight()->getDown());
			Assert::AreEqual(0x0A0, tree->getRight()->getDown()->getType());
			Assert::AreEqual(4U, tree->getRight()->getDown()->getOffset());

			// Skip character 'C' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(6U, context.getOffset());
		}
		TEST_METHOD(DownTreeTest)
		{
			char chars[] = "AABAAC";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);

			Data::Tree<Flow::Repeat<Data::Node<Char::Expect>::Pack>::Pack>::Pack<char>
				rule(Node<char>::Direction::Down, { { 0xA0, Node<char>::Direction::Left, { 'A' } } });

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());
			Assert::IsNotNull(tree->getLeft());
			Assert::AreEqual(0x0A0, tree->getLeft()->getType());
			Assert::AreEqual(1U, tree->getLeft()->getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B'
			context.forward(1);

			// Consume characters 'AA'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(5U, context.getOffset());
			Assert::IsNotNull(tree->getDown());
			Assert::AreEqual(0x0A0, tree->getDown()->getType());
			Assert::AreEqual(3U, tree->getDown()->getOffset());
			Assert::IsNotNull(tree->getDown()->getLeft());
			Assert::AreEqual(0x0A0, tree->getDown()->getLeft()->getType());
			Assert::AreEqual(4U, tree->getDown()->getLeft()->getOffset());

			// Skip character 'C' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(6U, context.getOffset());
		}
		TEST_METHOD(ExtractTest)
		{
			char chars[] = "BAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Extract<Data::Node<Char::Expect>::Pack>::Pack<char> rule(0xB0, { 0xA0, Node<char>::Direction::Left,  { 'A' } });

			// Skip character 'B' (to test length based on offset resolution)
			context.forward(1);

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(1U, tree->getOffset());
			Assert::IsNotNull(tree->getValue(0xB0));
			Assert::AreEqual('A', tree->getValue(0xB0)->getChar(0));
			Assert::AreEqual(1U, tree->getValue(0xB0)->getLength()); // Length based on offset resolution

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());
		}
		TEST_METHOD(RemarkTest)
		{
			char chars[] = "AB";
			char remark[] = "Hello world";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Remark<Data::Node<Char::Expect>::Pack>::Pack<char> rule(0xB0, { remark }, { 0xA0, Node<char>::Direction::Left, { 'A' } });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());
			Assert::IsNotNull(tree->getValue(0xB0));
			Assert::IsTrue(*tree->getValue(0xB0) == remark);

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(1U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());
		}
		TEST_METHOD(MatchTest)
		{
			char chars[] = "AAB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Data::Extract<Data::Node<Char::Expect>::Pack>::Pack<char> extract(0xB0, { 0xA0, Node<char>::Direction::Left,  { 'A' } });
			Data::Match<Char::Expect>::Pack<char> rule{ 0xB0, {'A'} };

			// Consume character 'A' using the extraction rule
			Assert::IsTrue(extract.consume(context));
			Assert::AreEqual(1U, context.getOffset());
			Assert::IsNotNull(tree);
			Assert::AreEqual(0x0A0, tree->getType());
			Assert::AreEqual(0U, tree->getOffset());
			Assert::IsNotNull(tree->getValue(0xB0));
			Assert::AreEqual('A', tree->getValue(0xB0)->getChar(0));

			// Consume character 'A' matching previous extraction
			Assert::IsTrue(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Can't consume character 'B'
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(2U, context.getOffset());

			// Skip character 'B' and reach the context end
			context.forward(1);

			// Can't consume next (reached the context end)
			Assert::IsFalse(rule.consume(context));
			Assert::AreEqual(3U, context.getOffset());
		}
	};
}
