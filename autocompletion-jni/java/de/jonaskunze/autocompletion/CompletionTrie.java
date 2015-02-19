package de.jonaskunze.autocompletion;

import java.util.List;

public class CompletionTrie {
    static {
        Autocompletion.initialize();
    }

    public class Suggestion {
        private String suggestion;
        private int relativeScore;
        private String additionalData;

        public Suggestion(String suggestion,
                          int relativeScore,
                          String additionalData) {
            this.suggestion = suggestion;
            this.relativeScore = relativeScore;
            this.additionalData = additionalData;
        }

        public String getSuggestion() {
            return suggestion;
        }

        public int getRelativeScore() {
            return relativeScore;
        }

        public String getAdditionalData() {
            return additionalData;
        }
    }

    public CompletionTrie() {
        init();
    }

    @Override
    public void finalize() {
        release();
    }

    private native void init();

    public native void release();

    public native List<Suggestion> getSuggestions(String prefix,
            int k);

    public native void print(boolean verbose);

    public native int getMemoryConsumption();
}
