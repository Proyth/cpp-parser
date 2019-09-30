// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../../Library/Source/Proyth.h"

#include "./Space.hpp"
#include "./String.hpp"
#include "./Name.hpp"

using namespace Proyth;
using namespace Proyth::Rules;

namespace Tokens {
	template<typename T>
	class Attribute : public Rule<T> {
	private:
		template<typename T>
		using Value = Flow::Any<String, String>::Pack<T>;
		template<typename T>
		using Assign = typename Flow::All<Char::Expect, Flow::Option<Space>::Pack, Value>::template Pack<T>;
		template<typename T>
		using Pack = typename Flow::All<Name, Flow::Option<Space>::Pack, Assign>::template Pack<T>;
		Pack<T> rule;
	public:
		template<unsigned N>
		Attribute(const T(&special)[N], const T& assign, const T& quoteA, const T& quoteB, const T& escape) :
			rule({ special }, { {} }, { assign, { {} }, { { quoteA, escape }, { quoteB, escape } } }) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}