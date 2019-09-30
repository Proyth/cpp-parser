// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Status {
	template<template<typename> class R>
	class Failure {
	public:
		template<typename T>
		class Pack : public Rule<T> {
			signed code;
			R<T> rule;
		public:
			Pack(const signed code, const R<T>& rule) :
				code(code), rule(rule) {}
			const bool consume(Context<T>& context) {
				if (!this->rule.consume(context)) {
					context.failure(code);
					return false;
				}
				return true;
			}
		};
	};
}