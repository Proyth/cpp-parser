// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Helpers/Copy.hpp"
#include "../../Helpers/Swap.hpp"
#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Char {
	template<typename T>
	class Choice : public Rule<T> {
	private:
		T* options;
		unsigned length;
	private:
		void swap(Choice<T>& other) {
			Helpers::Swap(other.options, this->options);
			Helpers::Swap(other.length, this->length);
		}
	public:
		template<unsigned N>
		Choice(const T(&options)[N]) :
			length(N), options(N > 0 ? new T[N] : nullptr) {
			Helpers::Copy(options, this->options, N);
		}
		Choice(const Choice<T>& other) :
			length(other.length), options(other.length > 0 ? new T[other.length] : nullptr) {
			Helpers::Copy(other.options, this->options, this->length);
		}
		Choice(Choice<T>&& other) :
			length(0), options(nullptr) {
			this->swap(other);
		}
		~Choice() {
			delete[] this->options;
		}
		const bool consume(Context<T>& context) {
			if (context.hasChars(1)) {
				const T current = context.getChar();
				for (unsigned i = 0; i < this->length; ++i) {
					if (this->options[i] == current) {
						context.forward(1);
						return true;
					}
				}
			}
			return false;
		}
		Choice& operator = (Choice<T> other) {
			this->swap(other);
			return *this;
		}
		Choice& operator = (Choice<T>&& other) {
			this->swap(other);
			return *this;
		}
	};
}