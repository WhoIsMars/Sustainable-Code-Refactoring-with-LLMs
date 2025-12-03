class Hamming {

    private final int hammingDistance;

    Hamming(String leftStrand, String rightStrand) {
        int leftLength = leftStrand.length();
        int rightLength = rightStrand.length();
        
        if (leftLength != rightLength) {
            if (leftLength == 0) {
                throw new IllegalArgumentException("left strand must not be empty.");
            } else if (rightLength == 0) {
                throw new IllegalArgumentException("right strand must not be empty.");
            } else {
                throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
            }
        }
        
        int distance = 0;
        for (int i = 0; i < leftLength; i++) {
            if (leftStrand.charAt(i) != rightStrand.charAt(i)) {
                distance++;
            }
        }
        this.hammingDistance = distance;
    }

    int getHammingDistance() {
        return hammingDistance;
    }
}