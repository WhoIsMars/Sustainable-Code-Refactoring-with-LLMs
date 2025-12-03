import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class PythagoreanTriplet {

    private final int a;
    private final int b;
    private final int c;

    public PythagoreanTriplet(int a, int b, int c) {
        int[] sorted = {a, b, c};
        java.util.Arrays.sort(sorted);
        this.a = sorted[0];
        this.b = sorted[1];
        this.c = sorted[2];
    }

    public int calculateSum() {
        return a + b + c;
    }

    public long calculateProduct() {
        return (long) a * b * c;
    }

    public boolean isPythagorean() {
        return a * a + b * b == c * c;
    }

    public static Builder makeTripletsList() {
        return new Builder();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PythagoreanTriplet that = (PythagoreanTriplet) o;
        return a == that.a && b == that.b && c == that.c;
    }

    @Override
    public int hashCode() {
        return Objects.hash(a, b, c);
    }

    static class Builder {

        private int minFactor = 2;
        private int maxFactor = Integer.MAX_VALUE;
        private long expectedSum = 0;

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
            for (int a = minFactor; a <= maxFactor - 2; a++) {
                for (int b = a + 1; b <= maxFactor - 1; b++) {
                    int c = (int) Math.sqrt(a * a + b * b);
                    if (c > maxFactor || c <= b) continue;
                    if (a * a + b * b == c * c) {
                        PythagoreanTriplet triplet = new PythagoreanTriplet(a, b, c);
                        if (expectedSum == 0 || triplet.calculateSum() == expectedSum) {
                            triplets.add(triplet);
                        }
                    }
                }
            }
            return triplets;
        }
    }
}