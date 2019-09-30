// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Strings/View.hpp"
#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Data {
	template<template<typename> class R>
	class Remark {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			unsigned key;
			Strings::View<T> value;
			R<T> rule;
		public:
			Pack(const unsigned key, const Strings::View<T>& value, const R<T>& rule) :
				key(key), value(value), rule(rule) {}
			const bool consume(Context<T>& context) {
				Proyth::Node<T>* tree = nullptr;
				Context<T> temp = Context<T>(context, tree);
				const bool status = this->rule.consume(temp);
				if (tree != nullptr) {
					tree->setValue(this->key, this->value);
					context.push(*tree, context.getDirection());
				}
				context.forward(temp);
				return status;
			}
		};
	};
}