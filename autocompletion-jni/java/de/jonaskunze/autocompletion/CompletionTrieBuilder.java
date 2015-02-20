package de.jonaskunze.autocompletion;

public class CompletionTrieBuilder {
    static {
        Autocompletion.initialize();
    }

    public static native CompletionTrie buildFromFile(String filename);
    
    public static native CompletionTrie buildFromFile(String filename, boolean verbose);
    
    private long nativeInstance;

    public CompletionTrieBuilder() {
        init();
    }

    private native void init();

    public native void release();

    public native void addString(String str,
                                 int score,
                                 String additionalData);

    public native CompletionTrie generateCompletionTrie();

    public native void print();

    public native float getAverageCharsPerNodes();

    public native int getNumberOfCharsStored();

    public native int getNumberOfWordsStored();
}
