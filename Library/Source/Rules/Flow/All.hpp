// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Flow {
	template<template<typename> class... N>
	class All;

	template<>
	class All<> {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		public:
			const bool consume(Context<T>& context) {
				return true;
			}
		};
	};

	template<template<typename> class R>
	class All<R> {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			R<T> rule;
		public:
			Pack(const R<T>& rule) :
				rule(rule) {}
			const bool consume(Context<T>& context) {
				return this->rule.consume(context);
			}
		};
	};

	template<template<typename> class R, template<typename> class... N>
	class All<R, N...> {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			R<T> rule;
			typename All<N...>::template Pack<T> next;
		public:
			Pack(const R<T>& rule, const N<T>&... next) :
				rule(rule), next(next...) {}
			const bool consume(Context<T>& context) {
				return this->rule.consume(context) && this->next.consume(context);
			}
		};
	};
}