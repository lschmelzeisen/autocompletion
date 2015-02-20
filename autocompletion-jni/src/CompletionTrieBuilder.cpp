#include "de_jonaskunze_autocompletion_CompletionTrieBuilder.h"

#include <iostream>

#include <jni.h>

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_buildFromFile
  (JNIEnv* /*env*/, jclass /*class_*/, jstring filename)
{
	std::cout << "CompletionTrieBuilder#buildFromFile(" << filename << ")" << std::endl;
	return nullptr;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_init
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#init()" << std::endl;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_release
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#release()" << std::endl;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_addString
  (JNIEnv* /*env*/, jobject /*instance*/, jstring str, jint score, jstring additionalData)
{
	std::cout << "CompletionTrieBuilder#addString(" << str << ", " << score << ", " << additionalData << ")" << std::endl;
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_generateCompletionTrie
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#generateCompletionTrie()" << std::endl;
	return nullptr;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_print
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#print()" << std::endl;
}

JNIEXPORT jfloat JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getAverageCharsPerNodes
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout  << "CompletionTrieBuilder#getAverageCharsPerNodes()" << std::endl;
	return 0.0f;
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfCharsStored
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#getNumberOfCharsStored()" << std::endl;
	return 0;
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfWordsStored
  (JNIEnv* /*env*/, jobject /*instance*/)
{
	std::cout << "CompletionTrieBuilder#getNumberOfWordsStored()" << std::endl;
	return 0;
}
