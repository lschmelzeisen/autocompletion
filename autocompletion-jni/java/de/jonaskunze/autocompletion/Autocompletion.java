package de.jonaskunze.autocompletion;

public class Autocompletion {
    private static boolean initialized = false;

    public static void initialize() {
        if (initialized)
            return;

        initialized = true;

        System.loadLibrary("autocompletion.jni");
        
        loadJNIEnvCache();
    }
    
    private static native void loadJNIEnvCache();

    static {
        initialize();
    }
}
