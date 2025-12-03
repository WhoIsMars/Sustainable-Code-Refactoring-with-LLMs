class CustomCheckedException extends Exception {

    CustomCheckedException() {
        super();
    }

    CustomCheckedException(String message) {
        super(message);
    }

    @Override
    public Throwable fillInStackTrace() {
        return this;
    }
}