// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../Flow/Repeat.hpp"
#include "../Flow/Any.hpp"
#include "./UpperAZ.hpp"
#include "./LowerAZ.hpp"

namespace Proyth::Rules::String {
	template<typename T>
	class AnyAZ : public Rule<T> {
	private:
		Flow::Repeat<Flow::Any<LowerAZ, UpperAZ>::Pack>::Pack<T> rule = { { {}, {} } };
	public:
		const bool consume(Context<T>& context) {
			return this->rule.consume(context);
		}
	};
}