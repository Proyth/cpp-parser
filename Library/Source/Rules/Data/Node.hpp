// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "../../Rule.hpp"
#include "../../Context.hpp"

namespace Proyth::Rules::Data {
	template<template<typename> class R>
	class Node {
	public:
		template<typename T>
		class Pack : public Rule<T> {
		private:
			using Direction = typename Proyth::Node<T>::Direction;
		private:
			signed type;
			Direction direction;
			R<T> rule;
		public:
			Pack(const signed type, const Direction direction, const R<T>& rule) :
				type(type), direction(direction), rule(rule) {}
			const bool consume(Context<T>& context) {
				const unsigned offset = context.getOffset();
				if (this->rule.consume(context)) {
					context.push(this->type, offset, this->direction);
					return true;
				}
				return false;
			}
		};
	};
}