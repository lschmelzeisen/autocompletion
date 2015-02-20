#include "de_jonaskunze_autocompletion_CompletionTrieBuilder.h"

#include <iostream>

#include <autocompletion/CompletionTrieBuilder.h>

#include "Exceptions.h"
#include "NativeInstance.h"

class CompletionTrie;

#define INSTANCE (NativeInstance<CompletionTrieBuilder>::get(env, instance))
#define INSTANCE_SET(pointer) (NativeInstance<CompletionTrieBuilder>::set(env, instance, (pointer)))

namespace {
	bool checkAlreadyReleased(JNIEnv* env, jobject instance) {
		if (INSTANCE == nullptr) {
			throwAlreadyReleasedException(env, "CompletionTrieBuilder already released.");
			return true;
		}
		return false;
	}

	jobject newCompletionTrieJava(JNIEnv* env) {
		return env->NewObject(JNIEnvCache::CompletionTrie, JNIEnvCache::CompletionTrie_Constructor);
	}
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_buildFromFile
  (JNIEnv* env, jclass /*class_*/, jstring filename)
{
	const char* filename_cstr = env->GetStringUTFChars(filename, nullptr);

	jobject completionTrieJava = newCompletionTrieJava(env);
	NativeInstance<CompletionTrie>::set(env, completionTrieJava, CompletionTrieBuilder::buildFromFile(filename_cstr));

	env->ReleaseStringUTFChars(filename, filename_cstr);

	return completionTrieJava;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_init
  (JNIEnv* env, jobject instance)
{
	INSTANCE_SET(new CompletionTrieBuilder);
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_release
  (JNIEnv* env, jobject instance)
{
	if (INSTANCE != nullptr) {
		delete INSTANCE;
		INSTANCE_SET(nullptr);
	}
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_addString
  (JNIEnv* env, jobject instance, jstring str, jint score, jstring additionalData)
{
	if (checkAlreadyReleased(env, instance))
		return;

	const char* str_cstr = env->GetStringUTFChars(str, nullptr);
	const char* additionalData_cstr = env->GetStringUTFChars(str, nullptr);

	INSTANCE->addString(str_cstr, score, additionalData_cstr);

	env->ReleaseStringUTFChars(str, str_cstr);
	env->ReleaseStringUTFChars(additionalData, additionalData_cstr);
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_generateCompletionTrie
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return nullptr;

	jobject completionTrieJava = newCompletionTrieJava(env);
	NativeInstance<CompletionTrie>::set(env, completionTrieJava, INSTANCE->generateCompletionTrie());
	return completionTrieJava;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_print
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return;

	INSTANCE->print();
	std::cout.flush();
}

JNIEXPORT jfloat JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getAverageCharsPerNodes
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return 0.0f;

	return static_cast<jfloat>(INSTANCE->getAverageCharsPerNode());
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfCharsStored
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return 0;

	return static_cast<jint>(INSTANCE->getNumberOfCharsStored());
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfWordsStored
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return 0;

	return static_cast<jint>(INSTANCE->getNumberOfWordsStored());
}
