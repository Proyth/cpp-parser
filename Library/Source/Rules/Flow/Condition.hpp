// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Flow {
	template<template<typename> class R, template<typename> class S, template<typename> class F>
	class Condition {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			R<T> rule;
			S<T> success;
			F<T> failure;
		public:
			Pack(const R<T>& rule, const S<T>& success, const F<T>& failure) :
				rule(rule), success(success), failure(failure) {}
			const bool consume(Context<T>& context) {
				Node<T>* tree = nullptr;
				Context<T> temp = Context<T>(context, tree);
				if (this->rule.consume(temp)) {
					if (tree) {
						context.push(*tree, context.getDirection());
					}
					context.forward(temp);
					return this->success.consume(context);
				}
				else {
					delete tree;
				}
				return this->failure.consume(context);
			}
		};
	};
}