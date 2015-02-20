#include "de_jonaskunze_autocompletion_Autocompletion.h"

#include "JNIEnvCache.h"

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_Autocompletion_loadJNIEnvCache
  (JNIEnv* env, jclass /*class_*/)
{
	JNIEnvCache::init(env);
}
