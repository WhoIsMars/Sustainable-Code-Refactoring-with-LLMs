class CustomCheckedException extends Exception {

    private static final long serialVersionUID = 1L;

    CustomCheckedException() {
        // Implicit super() call is already the most efficient way to construct the parent.
    }

    CustomCheckedException(String message) {
        super(message);
    }

}