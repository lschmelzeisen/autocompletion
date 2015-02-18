package de.jonaskunze.autocompletion;

public class CompletionTrie {
    static {
        System.loadLibrary("autocompletion.jni");
    }

    public native void foo();
}
