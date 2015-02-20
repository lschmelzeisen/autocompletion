package de.jonaskunze.autocompletion;

public class AlreadyReleasedException extends Exception {
    private static final long serialVersionUID = -3364010292944616327L;

    public AlreadyReleasedException() {
        super();
    }

    public AlreadyReleasedException(String message) {
        super(message);
    }

    public AlreadyReleasedException(Throwable cause) {
        super(cause);
    }

    public AlreadyReleasedException(String message,
                                    Throwable cause) {
        super(message, cause);
    }
}
