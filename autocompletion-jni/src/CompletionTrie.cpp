#include "de_jonaskunze_autocompletion_CompletionTrie.h"

#include <iostream>
#include <sstream>

#include <autocompletion/CompletionTrie.h>
#include <autocompletion/SuggestionList.h>

#include "Exceptions.h"
#include "NativeInstance.h"

#define INSTANCE (NativeInstance<CompletionTrie>::get(env, instance))
#define INSTANCE_SET(pointer) (NativeInstance<CompletionTrie>::set(env, instance, (pointer)))

namespace {
	bool checkAlreadyReleased(JNIEnv* env, jobject instance) {
		if (INSTANCE == nullptr) {
			throwAlreadyReleasedException(env, "CompletionTrie already released.");
			return true;
		}
		return false;
	}
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_release
  (JNIEnv* env, jobject instance)
{
	if (INSTANCE != nullptr) {
		delete INSTANCE;
		INSTANCE_SET(nullptr);
	}
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getSuggestions
  (JNIEnv* env, jobject instance, jstring prefix, jint k)
{
	if (checkAlreadyReleased(env, instance))
		return nullptr;

	if (k < 0) {
		std::stringstream ss;
		ss << "Parameter 'k' must not be negative, was: '" << k << "'.";
		throwIllegalArgumentException(env, ss.str().c_str());
		return nullptr;
	}

	const char* prefix_cstr = env->GetStringUTFChars(prefix, nullptr);

	long start = Utils::getCurrentMicroSeconds();
	std::cout << "Getting suggestions..." << std::endl;

	std::shared_ptr<SuggestionList> suggestionList = INSTANCE->getSuggestions(prefix_cstr, k);

	long time = Utils::getCurrentMicroSeconds();
	std::cout << "Suggestions gotten (took " << (time - start) << "us)" << std::endl;

	std::vector<Suggestion>& suggestions = suggestionList->suggestedWords;

	env->ReleaseStringUTFChars(prefix, prefix_cstr);

	start = Utils::getCurrentMicroSeconds();
	std::cout << "Creating array list..." << std::endl;

	jobject arraylist = env->NewObject(JNIEnvCache::ArrayList, JNIEnvCache::ArrayList_Constructor_Int, static_cast<jint>(suggestions.size()));
	for (auto suggestion : suggestions) {
		jstring suggestionSuggestion = env->NewStringUTF(suggestion.suggestion.c_str());
		jint suggestionRelativeScore = static_cast<jint>(suggestion.relativeScore);
		jstring suggestionAdditionalData = env->NewStringUTF(suggestion.additionalData.c_str());

		jobject javaSuggestion = env->NewObject(JNIEnvCache::Suggestion, JNIEnvCache::Suggestion_Constructor, suggestionSuggestion, suggestionRelativeScore, suggestionAdditionalData);
		env->CallBooleanMethod(arraylist, JNIEnvCache::ArrayList_Add_Object, javaSuggestion);
	}

	time = Utils::getCurrentMicroSeconds();
	std::cout << "Array list created (took " << (time - start) << "us)" << std::endl;

	return arraylist;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_print
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return;

	INSTANCE->print();
	std::cout.flush();
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getMemoryConsumption
  (JNIEnv* env, jobject instance)
{
	if (checkAlreadyReleased(env, instance))
		return 0;

	return static_cast<jint>(INSTANCE->getMemoryConsumption());
}
