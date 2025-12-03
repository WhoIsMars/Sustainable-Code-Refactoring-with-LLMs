class Hamming {

  private final int hammingDistance;

    Hamming(String leftStrand, String rightStrand) {
      int leftLen = leftStrand.length();
      int rightLen = rightStrand.length();
      
      if(leftLen != rightLen) {
        if(leftLen == 0) {
          throw new IllegalArgumentException("left strand must not be empty.");
        }
        else if(rightLen == 0) {
          throw new IllegalArgumentException("right strand must not be empty.");
        }
        else {
          throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }
      }
      
      int distance = 0;
      for(int i = 0; i < leftLen; i++) {
        if(leftStrand.charAt(i) != rightStrand.charAt(i)) {
          distance++;
        }
      }
      this.hammingDistance = distance;
    }

    int getHammingDistance() {
      return hammingDistance;
    }

}