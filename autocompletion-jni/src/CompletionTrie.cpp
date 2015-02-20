#include "de_jonaskunze_autocompletion_CompletionTrie.h"

#include <iostream>

#include <jni.h>

#include "NativeInstance.h"

#define INSTANCE (getNativeInstance<CompletionTrie>(env, instance))
#define INSTANCE_SET(pointer) (setNativeInstance<CompletionTrie>(env, instance, (pointer)))

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_release
  (JNIEnv* env, jobject instance)
{
	delete INSTANCE;
	INSTANCE_SET(nullptr);
}

JNIEXPORT jobject JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getSuggestions
  (JNIEnv* env, jobject instance, jstring prefix, jint k)
{

	jclass arraylistClass = env->FindClass("java/util/ArrayList");
	jmethodID arraylistConstructor = env->GetMethodID(arraylistClass, "<init>", "(I)V");
	jmethodID arraylistAdd = env->GetMethodID(arraylistClass, "add", "(Ljava/lang/Object;)Z");

	jclass suggestionClass = env->FindClass("de/jonaskunze/autocompletion/CompletionTrie$Suggestion");
	jmethodID suggestionConstructor = env->GetMethodID(suggestionClass, "<init>", "(Ljava/lang/String;ILjava/lang/String;)V");

	const char* prefix_cstr = env->GetStringUTFChars(prefix, nullptr);

	std::shared_ptr<SuggestionList> suggestionList = INSTANCE->getSuggestions(prefix_cstr, k);
	std::vector<Suggestion>& suggestions = suggestionList->suggestedWords;

	env->ReleaseStringUTFChars(prefix, prefix_cstr);

	jobject arraylist = env->NewObject(arraylistClass, arraylistConstructor, static_cast<jint>(suggestions.size()));
	for (auto suggestion : suggestions) {
		jstring suggestionSuggestion = env->NewStringUTF(suggestion.suggestion.c_str());
		jint suggestionRelativeScore = static_cast<jint>(suggestion.relativeScore);
		jstring suggestionAdditionalData = env->NewStringUTF(suggestion.additionalData.c_str());

		jobject javaSuggestion = env->NewObject(suggestionClass, suggestionConstructor, suggestionSuggestion, suggestionRelativeScore, suggestionAdditionalData);
		env->CallBooleanMethod(arraylist, arraylistAdd, javaSuggestion);
	}

	return arraylist;
}

JNIEXPORT void JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_print
  (JNIEnv* env, jobject instance)
{
	INSTANCE->print();
	std::cout.flush();
}

JNIEXPORT jint JNICALL Java_de_jonaskunze_autocompletion_CompletionTrie_getMemoryConsumption
  (JNIEnv* env, jobject instance)
{
	return static_cast<jint>(INSTANCE->getMemoryConsumption());
}
