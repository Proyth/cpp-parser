// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../Helpers/Copy.hpp"
#include "./View.hpp"

namespace Proyth::Strings {
	template<typename T>
	class Source : public View<T> {
	public:
		Source() :
			View<T>() {}
		template<unsigned N>
		Source(const T(&string)[N]) :
			View<T>((N - 1) > 0 ? new T[N - 1] : nullptr, N - 1) {
			Helpers::Copy(string, this->string, N - 1);
		}
		Source(const Source<T>& other) :
			View<T>(other.length > 0 ? new T[other.length] : nullptr, other.length) {
			Helpers::Copy(other.string, this->string, this->length);
		}
		Source(Source<T>&& other) :
			Source<T>() {
			this->swap(other);
		}
		~Source() {
			delete[] this->string;
			this->string = nullptr;
		}
		Source<T>& operator = (Source<T> other) {
			this->swap(other);
			return *this;
		}
		Source<T>& operator = (Source<T>&& other) {
			this->swap(other);
			return *this;
		}
	};
}