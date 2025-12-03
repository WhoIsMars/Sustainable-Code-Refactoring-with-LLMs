import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class PythagoreanTriplet {

    private final int[] sides;
    private final int sum;
    private final long product;

    public PythagoreanTriplet(int a, int b, int c) {
        sides = new int[]{a, b, c};
        Arrays.sort(sides);
        sum = sides[0] + sides[1] + sides[2];
        product = (long) sides[0] * sides[1] * sides[2];
    }

    public int calculateSum() {
        return sum;
    }

    public long calculateProduct() {
        return product;
    }

    public boolean isPythagorean() {
        int a = sides[0];
        int b = sides[1];
        int c = sides[2];
        return a * a + b * b == c * c;
    }

    public static Builder makeTripletsList() {
        return new Builder();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        return Arrays.equals(sides, ((PythagoreanTriplet) o).sides);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(sides);
    }

    static class Builder {

        private int minFactor = 2;
        private int maxFactor = Integer.MAX_VALUE;
        private long expectedSum;

        public Builder withFactorsGreaterThanOrEqualTo(int minFactor) {
            this.minFactor = minFactor;
            return this;
        }

        public Builder withFactorsLessThanOrEqualTo(int maxFactor) {
            this.maxFactor = maxFactor;
            return this;
        }

        public Builder thatSumTo(long expectedSum) {
            this.expectedSum = expectedSum;
            return this;
        }

        public List<PythagoreanTriplet> build() {
            final ArrayList<PythagoreanTriplet> triplets = new ArrayList<>();
            
            for (int a = minFactor; a <= maxFactor; a++) {
                for (int b = minFactor; b <= a; b++) {
                    int cSquared = a * a + b * b;
                    int c = (int) Math.sqrt(cSquared);
                    
                    if (c * c == cSquared && c >= minFactor && c <= maxFactor) {
                        final PythagoreanTriplet triplet = new PythagoreanTriplet(a, b, c);
                        if (expectedSum == 0 || expectedSum == triplet.calculateSum()) {
                            boolean exists = false;
                            for (PythagoreanTriplet existing : triplets) {
                                if (existing.equals(triplet)) {
                                    exists = true;
                                    break;
                                }
                            }
                            if (!exists) {
                                triplets.add(triplet);
                            }
                        }
                    }
                }
            }
            return triplets;
        }
    }
}