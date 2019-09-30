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
	class Comment : public Rule<T> {
	private:
		template<typename T>
		using Content = typename Flow::Repeat<Flow::Condition<Rules::String::Expect, Flow::False, Char::Any>::Pack>::template Pack<T>;
		template<typename T>
		using Pack = typename Flow::All<Rules::String::Expect, Content, Rules::String::Expect>::template Pack<T>;
		Pack<T> rule;
	public:
		Comment(const Strings::View<T>& open, const Strings::View<T>& close) :
			rule(open, { {  close, {}, {} } }, close) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}