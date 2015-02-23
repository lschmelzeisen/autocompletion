#include "Exceptions.h"

jint throwIllegalArgumentException(JNIEnv* env, const char* message) {
	return env->ThrowNew(JNIEnvCache::IllegalArgumentException, message);
}

jint throwAlreadyReleasedException(JNIEnv* env, const char* message) {
	return env->ThrowNew(JNIEnvCache::AlreadyReleasedException, message);
}
