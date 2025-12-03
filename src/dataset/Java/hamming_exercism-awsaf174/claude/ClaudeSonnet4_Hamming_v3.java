class Hamming {

    private final int hammingDistance;

    Hamming(String leftStrand, String rightStrand) {
        if (leftStrand.length() != rightStrand.length()) {
            if (leftStrand.isEmpty()) {
                throw new IllegalArgumentException("left strand must not be empty.");
            } else if (rightStrand.isEmpty()) {
                throw new IllegalArgumentException("right strand must not be empty.");
            } else {
                throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
            }
        }
        
        int distance = 0;
        int length = leftStrand.length();
        for (int i = 0; i < length; i++) {
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