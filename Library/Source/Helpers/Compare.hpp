// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

namespace Proyth::Helpers {
	template<typename T>
	const signed Compare(const T* const source, const T* const target, const unsigned length) {
		for (unsigned i = 0; i < length; ++i) {
			if (source[i] != target[i]) {
				return source[i] - target[i];
			}
		}
		return 0;
	}
}