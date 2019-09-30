// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Data {
	template<template<typename> class R>
	class Extract {
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
				const bool status = this->rule.consume(temp);
				if (tree != nullptr) {
					const unsigned offset = temp.getOffset() - context.getOffset();
					const Strings::View<T> value = context.getView(context.getOffset(), offset);
					tree->setValue(this->key, value);
					context.push(*tree, context.getDirection());
				}
				context.forward(temp);
				return status;
			}
		};
	};
}