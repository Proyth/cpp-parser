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
	TEST_CLASS(StatusTest)
	{
	public:
		TEST_METHOD(FailureTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Status::Failure<Char::Expect>::Pack<char> rule(0xA0, { 'A' });

			// Consume character 'A'
			Assert::IsTrue(rule.consume(context));
			Assert::IsFalse(context.hasError());
			Assert::AreEqual(1U, context.getOffset());

			// Can't consume character 'B' and fail
			Assert::IsFalse(rule.consume(context));
			Assert::IsTrue(context.hasError());
			Assert::AreEqual(1U, context.getError().getOffset());
			Assert::AreEqual(0xA0, context.getError().getCode());
			Assert::AreEqual(1U, context.getOffset());
		}
		TEST_METHOD(SuccessTest)
		{
			char chars[] = "AB";
			Node<char>* tree = nullptr;
			Context<char> context(chars, tree);
			Status::Success<Char::Expect>::Pack<char> rule({ 'B' });

			// Can't consume character 'A' and fail
			Assert::IsFalse(Status::Failure<Char::Expect>::Pack<char>(0xA0, { 'B' }).consume(context));
			Assert::IsTrue(context.hasError());
			Assert::AreEqual(0U, context.getOffset());

			// Skip character 'A'
			context.forward(1);

			// Consume character 'B' and succeed
			Assert::IsTrue(rule.consume(context));
			Assert::IsFalse(context.hasError());
			Assert::AreEqual(2U, context.getOffset());
		}
	};
}
