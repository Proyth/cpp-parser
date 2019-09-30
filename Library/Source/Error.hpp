// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

namespace Proyth {
	class Error {
	private:
		signed code;
		unsigned offset;
	public:
		Error(const signed code, const unsigned offset) :
			code(code), offset(offset) {}
		const signed getCode() const {
			return this->code;
		}
		const unsigned getOffset() const {
			return this->offset;
		}
	};
}