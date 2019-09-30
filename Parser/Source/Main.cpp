// This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code.
// Copyright (C) 2019 Silas B. Domingos
// All rights reserved.
//
#include <iostream>
#include "../../Library/Source/Proyth.h"

#include "./Tokens.h"

int main() {

	char chars[] = "<my-html  class='test' data-custom=\"test\">test</my-html>";
	Proyth::Node<char>* tree = nullptr;
	Proyth::Context<char> context(chars, tree);
	Tokens::Element<char> rule('<', { '-', '_' }, '=', '\'', '"', '\\', '/', '>');

	std::cout << rule.consume(context) << std::endl;
	std::cout << context.getOffset() << ":" << context.getLength() << std::endl;

	return 0;
}