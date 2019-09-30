// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../Helpers/Swap.hpp"
#include "../Helpers/Compare.hpp"

namespace Proyth::Strings {
	template<typename T>
	class View {
	protected:
		T* string;
		unsigned length;
	protected:
		View(T* string, const unsigned& length) :
			string(string), length(length) {}
		void swap(View<T>& other) {
			Helpers::Swap(this->string, other.string);
			Helpers::Swap(this->length, other.length);
		}
	public:
		View() :
			length(0), string(nullptr) {}
		View(const View<T>& other) :
			length(other.length), string(other.string) {}
		template<unsigned N>
		View(T(&string)[N]) :
			length(N - 1), string(string) {}
		const T getChar(const unsigned index) const {
			if (index < this->length) {
				return this->string[index];
			}
			return T();
		}
		const View<T> getView(const unsigned start, const unsigned length) const {
			if (start < this->length) {
				return View<T>(&this->string[start], length > this->length ? this->length : length);
			}
			return View<T>();
		}
		const unsigned getLength() const {
			return this->length;
		}
		View<T>& operator = (View<T> other) {
			this->swap(other);
			return *this;
		}
		const bool operator == (const View<T>& other) const {
			if (this->length == other.length) {
				return  Helpers::Compare(this->string, other.string, other.length) == 0;
			}
			return false;
		}
	};
}