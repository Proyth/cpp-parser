// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "./Range.hpp"

namespace Proyth::Rules::Char {
	template<typename T>
	class LowerAZ : public Rule<T> {
	public:
		Range<T> rule = { 'a', 'z' };
	public:
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}