#include "Exceptions.h"

jint throwAlreadyReleasedException(JNIEnv* env, const char* message) {
	return env->ThrowNew(JNIEnvCache::AlreadyReleasedException, message);
}
