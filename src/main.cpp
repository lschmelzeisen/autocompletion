//============================================================================
// Name        : main.cpp
// Author      : Jonas Kunze
// Version     :
// Copyright   : GPLv3
// Description : Main method of the autocompletion service
//============================================================================

//#include <cstring>

#include <deque>
#include <iostream>

#include "CompletionTrie.h"
#include "CompletionTrieBuilder.h"

using namespace std;

int main() {
	CompletionTrieBuilder builder;

	builder.addString("a", 1234);
	builder.addString("ab", 1235);
	builder.addString("abd", 1236);
	builder.addString("bcd", 1236);
	builder.addString("bdd", 1236);

	CompletionTrie* trie = builder.generateCompletionTrie();

	builder.print();

	trie->print();

//
//	bool return_foundTerm;
//	CompletionTrie trie;
//	trie.addTerm("12345", 1234);
//	trie.print();
//	std::cout << std::endl;
//	trie.addTerm("123456", 1234);
//	trie.print();
//	std::cout << std::endl;
//	trie.addTerm("abcd", 1234);
//	trie.print();
//	std::cout << std::endl;
//	trie.addTerm("abcd1", 1234);
//	trie.print();
//	std::cout << std::endl;
//	trie.addTerm("abcd12", 1234);
//	trie.print();
//	std::cout << std::endl;
//	trie.addTerm("123457", 1234);
//	trie.print();
//	std::cout << std::endl;
//
//	std::cout << trie.findLocus("asdf123", return_foundTerm).size() << " : ";
//	std::cout << return_foundTerm << std::endl;

	return 0;
}
