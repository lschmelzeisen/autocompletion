#include "de_jonaskunze_autocompletion_CompletionTrie.h"

#include <iostream>

#include <jni.h>

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_init
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrie#init()" << std::endl;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_release
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrie#release()" << std::endl;
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getSuggestions
  (JNIEnv* /*env*/, jobject /*instance*/, jstring prefix, jint k)
{
	std::cout << "CompletionTrie#getSuggestions(" << prefix << ", " << k << ")" << std::endl;
	return nullptr;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_print
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrie#print()" << std::endl;
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getMemoryConsumption
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrie#getMemoryConsumption()" << std::endl;
	return 0;
}
