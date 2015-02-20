#include "JNIEnvCache.h"

namespace JNIEnvCache {

namespace {
	jclass getGlobalClassRef(JNIEnv* env, const char* name) {
		jclass local = env->FindClass(name);
		jclass global = static_cast<jclass>(env->NewGlobalRef(local));
		env->DeleteLocalRef(local);
		return global;
	}
}

jclass    ArrayList                            = nullptr;
jmethodID ArrayList_Constructor_Int            = nullptr;
jmethodID ArrayList_Add_Object                 = nullptr;

jclass    CompletionTrie                       = nullptr;
jfieldID  CompletionTrie_NativeInstance        = nullptr;
jmethodID CompletionTrie_Constructor           = nullptr;

jclass    CompletionTrieBuilder                = nullptr;
jfieldID  CompletionTrieBuilder_NativeInstance = nullptr;

jclass    Suggestion                           = nullptr;
jmethodID Suggestion_Constructor               = nullptr;

void init(JNIEnv* env) {
	ArrayList                            = getGlobalClassRef(env, "java/util/ArrayList");
	ArrayList_Constructor_Int            = env->GetMethodID(ArrayList, "<init>", "(I)V");
	ArrayList_Add_Object                 = env->GetMethodID(ArrayList, "add",    "(Ljava/lang/Object;)Z");

	CompletionTrie                       = getGlobalClassRef(env, "de/jonaskunze/autocompletion/CompletionTrie");
	CompletionTrie_NativeInstance        = env->GetFieldID(CompletionTrie, "nativeInstance", "J");
	CompletionTrie_Constructor           = env->GetMethodID(CompletionTrie, "<init>",        "()V");

	CompletionTrieBuilder                = getGlobalClassRef(env, "de/jonaskunze/autocompletion/CompletionTrieBuilder");
	CompletionTrieBuilder_NativeInstance = env->GetFieldID(CompletionTrieBuilder, "nativeInstance", "J");

	Suggestion                           = getGlobalClassRef(env, "de/jonaskunze/autocompletion/CompletionTrie$Suggestion");
	Suggestion_Constructor               = env->GetMethodID(Suggestion, "<init>", "(Ljava/lang/String;ILjava/lang/String;)V");
}

}
