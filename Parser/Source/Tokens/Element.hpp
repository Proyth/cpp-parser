// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../../Library/Source/Proyth.h"

#include "./Space.hpp"
#include "./Name.hpp"
#include "./Attribute.hpp"

using namespace Proyth;
using namespace Proyth::Rules;

namespace Tokens {
	template<typename T>
	class Element : public Rule<T> {
	private:
		template<typename T>
		using OptionalSpace = Flow::Option<Space>::Pack<T>;
		template<typename T>
		using Attributes = typename Flow::Option<Flow::Repeat<Flow::All<Attribute, OptionalSpace>::Pack>::Pack>::template Pack<T>;
		template<typename T>
		using Open = typename Flow::All<Char::Expect, OptionalSpace, Name, OptionalSpace, Attributes, Flow::Option<Char::Expect>::Pack, OptionalSpace, Char::Expect>::template Pack<T>;
		template<typename T>
		using Pack = Open<T>;
		Pack<T> rule;
	public:
		template<unsigned N>
		Element(const T& tagOpen, const T(&special)[N], const T& assign, const T& quoteA, const T& quoteB, const T& escape, const T& tagSlash, const T& tagClose) :
			rule(tagOpen, { {} }, { special }, { {} }, { { { { special, assign, quoteA, quoteB, escape }, { {} } } } }, { tagSlash }, { {} }, tagClose) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}