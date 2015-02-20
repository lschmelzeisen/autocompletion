#ifndef INSTANCEPOINTER_H_
#define INSTANCEPOINTER_H_

#include "JNIEnvCache.h"

class CompletionTrie;
class CompletionTrieBuilder;

template <typename T>
class NativeInstance {
public:
	static void set(JNIEnv* env, jobject instance, T* nativeInstance) {
		jclass class_ = env->GetObjectClass(instance);
		jfieldID field = env->GetFieldID(class_, "nativeInstance", "J");
		env->SetLongField(instance, field, reinterpret_cast<jlong>(nativeInstance));
	}

	static T* get(JNIEnv* env, jobject instance) {
		jclass class_ = env->GetObjectClass(instance);
		jfieldID field = env->GetFieldID(class_, "nativeInstance", "J");
		jlong nativeInstance = env->GetLongField(instance, field);
		return reinterpret_cast<T*>(nativeInstance);
	}
};

template <>
class NativeInstance<CompletionTrie> {
public:
	static void set(JNIEnv* env, jobject instance, CompletionTrie* nativeInstance) {
		env->SetLongField(instance, JNIEnvCache::CompletionTrie_NativeInstance, reinterpret_cast<jlong>(nativeInstance));
	}

	static CompletionTrie* get(JNIEnv* env, jobject instance) {
		jlong nativeInstance = env->GetLongField(instance, JNIEnvCache::CompletionTrie_NativeInstance);
		return reinterpret_cast<CompletionTrie*>(nativeInstance);
	}
};

template<>
class NativeInstance<CompletionTrieBuilder> {
public:
	static void set(JNIEnv* env, jobject instance, CompletionTrieBuilder* nativeInstance) {
		env->SetLongField(instance, JNIEnvCache::CompletionTrieBuilder_NativeInstance, reinterpret_cast<jlong>(nativeInstance));
	}

	static CompletionTrieBuilder* get(JNIEnv* env, jobject instance) {
		jlong nativeInstance = env->GetLongField(instance, JNIEnvCache::CompletionTrieBuilder_NativeInstance);
		return reinterpret_cast<CompletionTrieBuilder*>(nativeInstance);
	}
};

#endif /* INSTANCEPOINTER_H_ */
