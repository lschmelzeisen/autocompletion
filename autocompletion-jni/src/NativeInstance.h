#ifndef INSTANCEPOINTER_H_
#define INSTANCEPOINTER_H_

#include <jni.h>

#include <autocompletion/CompletionTrie.h>
#include <autocompletion/CompletionTrieBuilder.h>

template <typename T>
void setNativeInstance(JNIEnv* env, jobject instance, T* nativeInstance) {
	jclass class_ = env->GetObjectClass(instance);
	jfieldID field = env->GetFieldID(class_, "nativeInstance", "J");
	env->SetLongField(instance, field, reinterpret_cast<jlong>(nativeInstance));
}

template <typename T>
T* getNativeInstance(JNIEnv* env, jobject instance) {
	jclass class_ = env->GetObjectClass(instance);
	jfieldID field = env->GetFieldID(class_, "nativeInstance", "J");
	jlong nativeInstance = env->GetLongField(instance, field);
	return reinterpret_cast<T*>(nativeInstance);
}

#endif /* INSTANCEPOINTER_H_ */
