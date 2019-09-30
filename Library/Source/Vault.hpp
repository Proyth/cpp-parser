// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#pragma once

namespace Proyth {
	template<typename K, typename V>
	class Vault {
	private:
		class Node {
		public:
			K key;
			V value;
			bool finish = false;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* down = nullptr;
			Node(const K& key) :
				key(key), value() {}
			~Node() {
				delete this->left;
				delete this->right;
				delete this->down;
			}
		};
	private:
		Node* root = nullptr;
		unsigned length = 0;
	private:
		Node*& lookup(const K& key, Node*& node) const {
			Node** current = &node;
			while (*current != nullptr) {
				const K difference = (*current)->key - key;
				if (difference < 0) {
					current = &(*current)->left;
				}
				else if (difference > 0) {
					current = &(*current)->right;
				}
				else {
					break;
				}
			}
			return *current;
		}
	public:
		~Vault() {
			delete this->root;
		}
		template<unsigned N>
		void setValue(const K(&key)[N], const V& value) {
			Node** current = &this->root;
			const unsigned length = N - 1;
			for (unsigned i = 0; i < length; ++i) {
				if ((*(current = &this->lookup(key[i], *current))) == nullptr) {
					*current = new Node(key[i]);
				}
				if (i + 1 == length) {
					(*current)->finish = true;
					(*current)->value = value;
					this->length++;
				}
				current = &(*current)->down;
			}
		}
		template<unsigned N>
		V* getValue(const K(&key)[N]) const {
			Node* current = this->root;
			if (current != nullptr) {
				const unsigned length = N - 1;
				for (unsigned i = 0; i < length; ++i) {
					if ((current = this->lookup(key[i], current)) == nullptr) {
						return nullptr;
					}
				}
				if (current->finish) {
					return &current->value;
				}
			}
			return nullptr;
		}
		const unsigned getLength() const {
			return this->length;
		}
	};
}