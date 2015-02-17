/*
 * SuggestionList.h
 *
 *  Created on: Nov 10, 2013
 *      Author: Jonas Kunze
 */

#include <autocompletion/SuggestionList.h>

#include <autocompletion/CompletionTrie.h>
#include <autocompletion/PackedNode.h>
#include <autocompletion/SuggestionStore.h>

void SuggestionList::addSuggestion(NodeWithRelativeScoreStore nodeWithParent) {
	suggestedWords.push_back(
			{ nodeWithParent.getString(), nodeWithParent.getRelativeScore(),
					store->getAdditionalData(nodeWithParent.node) });
}
