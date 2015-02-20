#ifndef JNIENVCACHE_H_
#define JNIENVCACHE_H_

#include <jni.h>

namespace JNIEnvCache {

extern jclass    ArrayList;
extern jmethodID ArrayList_Constructor_Int;
extern jmethodID ArrayList_Add_Object;

extern jclass    CompletionTrie;
extern jfieldID  CompletionTrie_NativeInstance;
extern jmethodID CompletionTrie_Constructor;

extern jclass    CompletionTrieBuilder;
extern jfieldID  CompletionTrieBuilder_NativeInstance;

extern jclass    Suggestion;
extern jmethodID Suggestion_Constructor;

void init(JNIEnv* env);

}

#endif /* JNIENVCACHE_H_ */
