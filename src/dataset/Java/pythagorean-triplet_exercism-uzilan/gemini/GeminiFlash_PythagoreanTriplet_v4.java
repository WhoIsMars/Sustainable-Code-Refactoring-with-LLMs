import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Arrays;

public class PythagoreanTriplet {

    private final int[] sides;

    public PythagoreanTriplet(int a, int b, int c) {
        sides = new int[]{a, b, c};
        Arrays.sort(sides);
    }

    public int calculateSum() {
        return sides[0] + sides[1] + sides[2];
    }

    public long calculateProduct() {
        return (long) sides[0] * sides[1] * sides[2];
    }

    public boolean isPythagorean() {
        return square(sides[0]) + square(sides[1]) == square(sides[2]);
    }

    private int square(int number) {
        return number * number;
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
        PythagoreanTriplet that = (PythagoreanTriplet) o;
        return Arrays.equals(sides, that.sides);
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
            List<PythagoreanTriplet> triplets = new ArrayList<>();
            for (int a = minFactor; a <= maxFactor; a++) {
                for (int b = a + 1; b <= maxFactor; b++) {
                    int cSquared = a * a + b * b;
                    int c = (int) Math.sqrt(cSquared);

                    if (c > maxFactor || c * c != cSquared) {
                        continue;
                    }

                    PythagoreanTriplet triplet = new PythagoreanTriplet(a, b, c);

                    if (expectedSum == 0 || expectedSum == triplet.calculateSum()) {
                        triplets.add(triplet);
                    }
                }
            }
            return triplets;
        }
    }
}