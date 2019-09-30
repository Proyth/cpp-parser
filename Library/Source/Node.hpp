// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

#include "./Strings/View.hpp"
#include "./Vault.hpp"

namespace Proyth {
	template<typename T>
	class Node {
	public:
		enum class Direction : unsigned {
			Left = 0x1,
			Right,
			Down
		};
	private:
		signed type;
		unsigned offset;
		Vault<unsigned, Strings::View<T>> vault;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* down = nullptr;
	public:
		Node(signed type, unsigned offset) :
			type(type), offset(offset) {}
		~Node() {
			delete this->left;
			delete this->right;
			delete this->down;
		}
		const signed getType() const {
			return this->type;
		}
		const unsigned getOffset() const {
			return this->offset;
		}
		const Node* getLeft() const {
			return this->left;
		}
		const Node* getRight() const {
			return this->right;
		}
		const Node* getDown() const {
			return this->down;
		}
		const Strings::View<T>* getValue(const unsigned key) {
			return this->vault.getValue({ key, 0x00 });
		}
		void setValue(const unsigned key, const Strings::View<T>& value) {
			this->vault.setValue({ key, 0x00 }, value);
		}
	private:
		static Node*& getLast(Node*& node, const Direction direction) {
			Node** current = &node;
			while (*current) {
				switch (direction) {
				case(Direction::Left):
					current = &(*current)->left;
					break;
				case(Direction::Right):
					current = &(*current)->right;
					break;
				case(Direction::Down):
					current = &(*current)->down;
					break;
				}
			}
			return (*current);
		}
	public:
		static Node*& push(Node*& current, Node& newer, const Direction direction) {
			switch (direction) {
			case(Direction::Left):
				return Node::getLast((current = &newer)->left, direction);
			case(Direction::Right):
				return Node::getLast((current = &newer)->right, direction);
			case(Direction::Down):
				return Node::getLast((current = &newer)->down, direction);
			}
			return current;
		}
	};
}