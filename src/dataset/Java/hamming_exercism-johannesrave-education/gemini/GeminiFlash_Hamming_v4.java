public class Hamming {

    private final char[] left;
    private final char[] right;

    public Hamming(String leftStrand, String rightStrand) {
        int leftLength = leftStrand.length();
        int rightLength = rightStrand.length();

        if (leftLength != rightLength) {
            if (leftLength == 0) {
                throw new IllegalArgumentException("left strand must not be empty.");
            }
            if (rightLength == 0) {
                throw new IllegalArgumentException("right strand must not be empty.");
            }
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }

        this.left = leftStrand.toCharArray();
        this.right = rightStrand.toCharArray();
    }

    public int getHammingDistance() {
        int distance = 0;
        char[] leftArr = this.left;
        char[] rightArr = this.right;
        int length = leftArr.length;

        for (int i = 0; i < length; i++) {
            if (leftArr[i] != rightArr[i]) {
                distance++;
            }
        }
        return distance;
    }
}