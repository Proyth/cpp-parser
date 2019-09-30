// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Status {
	template<template<typename> class R>
	class Success {
	public:
		template<typename T>
		class Pack : public Rule<T> {
			R<T> rule;
		public:
			Pack(const R<T>& rule) :
				rule(rule) {}
			const bool consume(Context<T>& context) {
				if (this->rule.consume(context)) {
					context.success();
					return true;
				}
				return false;
			}
		};
	};
}