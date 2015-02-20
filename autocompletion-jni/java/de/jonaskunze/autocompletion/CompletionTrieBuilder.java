package de.jonaskunze.autocompletion;

public class CompletionTrieBuilder {
    static {
        Autocompletion.initialize();
    }

    public static native CompletionTrie buildFromFile(String fileName);
    
    public static native CompletionTrie buildFromFile(String fileName,
                                                      boolean verbose);
    
    public static native CompletionTrie buildFromFile(String fileName,
                                                      boolean verbose,
                                                      boolean caseSensitive);
    
    private long nativeInstance;

    public CompletionTrieBuilder() {
        this(false);
    }
    
    public CompletionTrieBuilder(boolean caseSensitive) {
        init(caseSensitive);
    }

    private native void init(boolean caseSensitive);

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
