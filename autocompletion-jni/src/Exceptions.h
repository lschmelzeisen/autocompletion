#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "JNIEnvCache.h"

jint throwAlreadyReleasedException(JNIEnv* env, const char* message);

#endif /* EXCEPTIONS_H_ */
