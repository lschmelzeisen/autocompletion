#include "de_jonaskunze_autocompletion_CompletionTrieBuilder.h"

#include <iostream>

#include <jni.h>

#include "NativeInstance.h"

#define INSTANCE (getNativeInstance<CompletionTrieBuilder>(env, instance))
#define INSTANCE_SET(pointer) (setNativeInstance<CompletionTrieBuilder>(env, instance, (pointer)))

namespace {
	jobject newCompletionTrieJava(JNIEnv* env) {
		jclass class_ = env->FindClass("de/jonaskunze/autocompletion/CompletionTrie");
		jmethodID constructor = env->GetMethodID(class_, "<init>", "()V");
		jobject completionTrieJava = env->NewObject(class_, constructor);
		return completionTrieJava;
	}
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_buildFromFile
  (JNIEnv* env, jclass /*class_*/, jstring filename)
{
	const char* filename_cstr = env->GetStringUTFChars(filename, nullptr);

	jobject completionTrieJava = newCompletionTrieJava(env);
	setNativeInstance<CompletionTrie>(env, completionTrieJava, CompletionTrieBuilder::buildFromFile(filename_cstr));

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
	delete INSTANCE;
	INSTANCE_SET(nullptr);
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_addString
  (JNIEnv* env, jobject instance, jstring str, jint score, jstring additionalData)
{
	const char* str_cstr = env->GetStringUTFChars(str, nullptr);
	const char* additionalData_cstr = env->GetStringUTFChars(str, nullptr);

	INSTANCE->addString(str_cstr, score, additionalData_cstr);

	env->ReleaseStringUTFChars(str, str_cstr);
	env->ReleaseStringUTFChars(additionalData, additionalData_cstr);
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_generateCompletionTrie
  (JNIEnv* env, jobject instance)
{
	jobject completionTrieJava = newCompletionTrieJava(env);
	setNativeInstance<CompletionTrie>(env, completionTrieJava, INSTANCE->generateCompletionTrie());
	return completionTrieJava;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_print
  (JNIEnv* env, jobject instance)
{
	INSTANCE->print();
	std::cout.flush();
}

JNIEXPORT jfloat JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getAverageCharsPerNodes
  (JNIEnv* env, jobject instance)
{
	return static_cast<jfloat>(INSTANCE->getAverageCharsPerNode());
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfCharsStored
  (JNIEnv* env, jobject instance)
{
	return static_cast<jint>(INSTANCE->getNumberOfCharsStored());
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrieBuilder_getNumberOfWordsStored
  (JNIEnv* env, jobject instance)
{
	return static_cast<jint>(INSTANCE->getNumberOfWordsStored());
}
