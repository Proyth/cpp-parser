// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Char {
	template<typename T>
	class Range : public Rule<T> {
	private:
		T start;
		T end;
	public:
		Range(const T& start, const T& end) :
			start(start), end(end) {}
		const bool consume(Context<T>& context) {
			if (context.hasChars(1)) {
				const T current = context.getChar();
				if (current >= this->start && current <= this->end) {
					context.forward(1);
					return true;
				}
			}
			return false;
		}
	};
}