class CustomCheckedException extends Exception {

    private static final long serialVersionUID = 1L;

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