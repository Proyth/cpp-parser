// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

namespace Proyth::Helpers {
	template<typename T>
	T& Swap(T& source, T& target) {
		const T copy(target);
		target = source;
		source = copy;
		return target;
	}
}