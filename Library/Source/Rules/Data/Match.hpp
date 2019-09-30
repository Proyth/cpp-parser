// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Data {
	template<template<typename> class R>
	class Match {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			unsigned key;
			R<T> rule;
		public:
			Pack(const unsigned key, const R<T>& rule) :
				key(key), rule(rule) {}
			const bool consume(Context<T>& context) {
				Proyth::Node<T>* tree = nullptr;
				Context<T> temp = Context<T>(context, tree);
				if (this->rule.consume(temp) && context.hasTree()) {
					const unsigned offset = temp.getOffset() - context.getOffset();
					const Strings::View<T> consumed = context.getView(context.getOffset(), offset);
					const Strings::View<T>* expected = context.getTree()->getValue(this->key);
					if (expected != nullptr && *expected == consumed) {
						if (tree != nullptr) {
							context.push(*tree, context.getDirection());
						}
						context.forward(temp);
						return true;
					}
				}
				return false;
			}
		};
	};
}