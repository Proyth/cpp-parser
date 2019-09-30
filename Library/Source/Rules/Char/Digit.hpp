// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "./Range.hpp"

namespace Proyth::Rules::Char {
	template<typename T>
	class Digit : public Rule<T> {
	private:
		Range<T> rule = { '0', '9' };
	public:
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}