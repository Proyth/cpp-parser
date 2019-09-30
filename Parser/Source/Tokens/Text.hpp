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
	class Text : public Rule<T> {
	private:
		template<typename T>
		using Pack = Flow::Repeat<Flow::Condition<Char::Expect, Flow::False, Char::Any>::Pack>::Pack<T>;
		Pack<T> rule;
	public:
		Text(const T& tagClose) :
			rule({ tagClose , {}, {} }) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}