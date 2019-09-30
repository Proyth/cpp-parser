// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

namespace Proyth::Helpers {
	template<typename T>
	T* Copy(const T* const source, T* target, const unsigned length) {
		for (unsigned i = 0; i < length; ++i) {
			target[i] = source[i];
		}
		return target;
	}
}