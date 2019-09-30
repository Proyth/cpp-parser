// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Data {
	template<template<typename> class R>
	class Tree {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			using Direction = typename Proyth::Node<T>::Direction;
		private:
			Direction direction;
			R<T> rule;
		public:
			Pack(const Direction direction, const R<T>& rule) :
				direction(direction), rule(rule) {}
			const bool consume(Context<T>& context) {
				Proyth::Node<T>* tree = nullptr;
				Context<T> temp = Context<T>(context, tree);
				const bool status = this->rule.consume(temp);
				if (tree) {
					context.push(*tree, this->direction);
				}
				context.forward(temp);
				return status;
			}
		};
	};
}