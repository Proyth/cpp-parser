// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Strings/View.hpp"
#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::String {
	template<typename T>
	class Expect : public Rule<T> {
	private:
		Strings::View<T> expected;
	public:
		Expect(const Strings::View<T>& expected) :
			expected(expected) {}
		const bool consume(Context<T>& context) {
			if (context.hasChars(this->expected.getLength())) {
				Context<T> temp = Context<T>(context);
				for (unsigned i = 0; i < this->expected.getLength(); ++i) {
					if (this->expected.getChar(i) != temp.getChar()) {
						return false;
					}
					temp.forward(1);
				}
				context.forward(this->expected.getLength());
				return true;
			}
			return false;
		}
	};
}