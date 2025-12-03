import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

class PythagoreanTriplet {
    private final int num1;
    private final int num2;
    private final int num3;

    PythagoreanTriplet(int a, int b, int c) {
        this.num1 = a;
        this.num2 = b;
        this.num3 = c;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (!(o instanceof PythagoreanTriplet))
            return false;
        PythagoreanTriplet other = (PythagoreanTriplet) o;
        return num1 == other.num1 &&
                num2 == other.num2 &&
                num3 == other.num3;
    }

    @Override
    public int hashCode() {
        return Objects.hash(num1, num2, num3);
    }

    static TrippletCreator makeTripletsList() {
        return new TrippletCreator();
    }

    static class TrippletCreator {
        private int factorsLessThanOrEqualTo;
        private int sumTo;

        TrippletCreator withFactorsLessThanOrEqualTo(int value) {
            factorsLessThanOrEqualTo = value;
            return this;
        }

        TrippletCreator thatSumTo(int value) {
            sumTo = value;
            return this;
        }

        List<PythagoreanTriplet> build() {
            List<PythagoreanTriplet> triplets = new ArrayList<>();
            int maxI = Math.min(factorsLessThanOrEqualTo / 2, sumTo / 3);
            
            for (int i = 1; i <= maxI; i++) {
                int maxJ = Math.min((factorsLessThanOrEqualTo - i) / 2, (sumTo - i) / 2);
                for (int j = i + 1; j <= maxJ; j++) {
                    int k = sumTo - i - j;
                    if (k > j && k <= factorsLessThanOrEqualTo) {
                        long iSquared = (long) i * i;
                        long jSquared = (long) j * j;
                        long kSquared = (long) k * k;
                        if (iSquared + jSquared == kSquared) {
                            triplets.add(new PythagoreanTriplet(i, j, k));
                        }
                    }
                }
            }
            return triplets;
        }
    }
}