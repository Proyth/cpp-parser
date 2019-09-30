// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Strings/View.hpp"
#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::String {
	template<typename T>
	class Choice : public Rule<T> {
	private:
		Strings::View<T>* options;
		unsigned length;
	private:
		void swap(Choice<T>& other) {
			Helpers::Swap(other.options, this->options);
			Helpers::Swap(other.length, this->length);
		}
		const bool match(const Strings::View<T>& expected, Context<T>& context) const {
			Context<T> temp = Context<T>(context);
			for (unsigned i = 0; i < expected.getLength(); ++i) {
				if (expected.getChar(i) != temp.getChar()) {
					return false;
				}
				temp.forward(1);
			}
			return true;
		}
	public:
		template<unsigned N>
		Choice(const Strings::View<T>(&options)[N]) :
			length(N), options(N > 0 ? new Strings::View<T>[N] : nullptr) {
			Helpers::Copy(options, this->options, N);
		}
		Choice(const Choice<T>& other) :
			length(other.length), options(other.length > 0 ? new Strings::View<T>[other.length] : nullptr) {
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
			for (unsigned i = 0; i < this->length; ++i) {
				const Strings::View<T>& expected = this->options[i];
				if (context.hasChars(expected.getLength()) && match(expected, context)) {
					context.forward(expected.getLength());
					return true;
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