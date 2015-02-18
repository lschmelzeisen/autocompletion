#include "de_jonaskunze_autocompletion_CompletionTrie.h"

#include <stdio.h>

#include <jni.h>

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_foo(JNIEnv* env, jobject this) {
	(void) env;
	(void) this;
	printf("foo Junge!");
}
