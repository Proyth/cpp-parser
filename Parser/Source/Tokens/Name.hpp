// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../../Library/Source/Proyth.h"

#include "./Space.hpp"

using namespace Proyth;
using namespace Proyth::Rules;

namespace Tokens {
	template<typename T>
	class Name : public Rule<T> {
	private:
		template<typename T>
		using Pack = Flow::Repeat<Flow::Any<Rules::String::AnyAZ, Char::Choice>::Pack>::Pack<T>;
		Pack<T> rule;
	public:
		template<unsigned N>
		Name(const T(&special)[N]) :
			rule({ {}, { special } }) {}
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}