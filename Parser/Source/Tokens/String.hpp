// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../../Library/Source/Proyth.h"

using namespace Proyth;
using namespace Proyth::Rules;

namespace Tokens {
	template<typename T>
	class String : public Rule<T> {
	private:
		template<typename T>
		using Tail = Flow::Condition<Char::Expect, Flow::False, Char::Any>::Pack<T>;
		template<typename T>
		using Content = typename Flow::Repeat<Flow::Condition<Char::Expect, Char::Any, Tail>::Pack>::template Pack<T>;
		template<typename T>
		using Pack = typename Flow::All<Char::Expect, Content, Char::Expect>::template Pack<T>;
		Pack<T> rule;
	public:
		String(const T& quote, const T& escape) :
			rule({ { quote }, { { { escape }, {}, { { quote }, {}, {} } } }, { quote } }) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}