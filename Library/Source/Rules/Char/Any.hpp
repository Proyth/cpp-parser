// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Char {
	template<typename T>
	class Any : public Rule<T> {
	public:
		const bool consume(Context<T>& context) {
			if (context.hasChars(1)) {
				context.forward(1);
				return true;
			}
			return false;
		}
	};
}