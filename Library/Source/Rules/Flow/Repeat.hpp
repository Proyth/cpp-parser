// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Flow {
	template<template<typename> class R>
	class Repeat {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			R<T> rule;
		public:
			Pack(const R<T>& rule) :
				rule(rule) {}
			const bool consume(Context<T>& context) {
				if (this->rule.consume(context)) {
					while (context.getOffset() < context.getLength()) {
						Node<T>* tree = nullptr;
						Context<T> temp = Context<T>(context, tree);
						if (!this->rule.consume(temp)) {
							delete tree;
							break;
						}
						if (tree) {
							context.push(*tree, context.getDirection());
						}
						context.forward(temp);
					}
					return true;
				}
				return false;
			}
		};
	};
}