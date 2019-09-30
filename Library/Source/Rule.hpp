// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "./Context.hpp"
#include "./Helpers/NonCopyable.hpp"

namespace Proyth {
	template<typename T>
	class Rule {
	public:
		const bool consume(Context<T>& context) {
			static_assert("Method doesn't implemented.");
			return false;
		}
	};
}