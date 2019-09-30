// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "./Strings/View.hpp"
#include "./Error.hpp"
#include "./Node.hpp"

namespace Proyth {
	template<typename T>
	class Context {
	private:
		using Direction = typename Node<T>::Direction;
	private:
		Strings::View<T> input;
		unsigned offset;
		Error error;
		Node<T>** newTree;
		Node<T>* oldTree = nullptr;
		Direction direction = Direction::Down;
	public:
		template<unsigned N>
		Context(T(&input)[N], Node<T>*& tree) :
			input(input), offset(0), error(0, 0), newTree(&tree) {}
		Context(Context& other, Node<T>*& tree) :
			input(other.input), offset(other.offset), error(other.error), newTree(&tree) {}
		const bool hasChars(const unsigned length) const {
			return (this->offset + length) <= this->input.getLength();
		}
		const bool hasError() const {
			return this->error.getCode() != 0;
		}
		const bool hasTree() const {
			return this->oldTree != nullptr;
		}
		const T getChar() const {
			return this->input.getChar(this->offset);
		}
		const Strings::View<T> getView(const unsigned start, const unsigned length) const {
			return this->input.getView(start, length);
		}
		const unsigned getOffset() const {
			return this->offset;
		}
		const unsigned getLength() const {
			return this->input.getLength();
		}
		const Error& getError() const {
			return this->error;
		}
		Node<T>* getTree() const {
			return this->oldTree;
		}
		Direction getDirection() const {
			return this->direction;
		}
		Context<T>& forward(const unsigned length) {
			this->offset += length;
			return *this;
		}
		Context<T>& forward(const Context<T>& other) {
			this->offset = other.offset;
			this->error = other.error;
			return *this;
		}
		Context<T>& success() {
			this->error = Error(0, 0);
			return *this;
		}
		Context<T>& failure(const signed code) {
			this->error = Error(code, this->offset);
			return *this;
		}
		Context<T>& push(Node<T>& tree, const Direction direction) {
			this->oldTree = &tree;
			this->newTree = &Node<T>::push(*this->newTree, tree, direction);
			return *this;
		}
		Context<T>& push(const signed code, const unsigned offset, const Direction direction) {
			return this->push(*new Node<T>(code, offset), direction);
		}
	};
}