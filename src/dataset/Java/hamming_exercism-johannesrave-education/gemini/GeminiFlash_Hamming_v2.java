public class Hamming {

    private final String leftStrand;
    private final String rightStrand;
    private final int length;

    public Hamming(String leftStrand, String rightStrand) {
        this.leftStrand = leftStrand;
        this.rightStrand = rightStrand;
        this.length = leftStrand.length();

        if (length != rightStrand.length()) {
            if (length == 0) throw new IllegalArgumentException("left strand must not be empty.");
            if (rightStrand.isEmpty()) throw new IllegalArgumentException("right strand must not be empty.");
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }
    }

    public int getHammingDistance() {
        int distance = 0;
        for (int i = 0; i < length; i++) {
            if (leftStrand.charAt(i) != rightStrand.charAt(i)) {
                distance++;
            }
        }
        return distance;
    }
}