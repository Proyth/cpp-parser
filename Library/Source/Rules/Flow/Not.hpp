// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Flow {
	template<template<typename> class R>
	class Not {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			R<T> rule;
		public:
			Pack(const R<T>& rule) :
				rule(rule) {}
			const bool consume(Context<T>& context) {
				Context<T> temp = Context<T>(context);
				return !this->rule.consume(temp);
			}
		};
	};
}