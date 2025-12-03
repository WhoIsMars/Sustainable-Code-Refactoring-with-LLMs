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
            if (sumTo > 0 && factorsLessThanOrEqualTo > 0) {
                for (int a = 1; a <= factorsLessThanOrEqualTo; a++) {
                    for (int b = a + 1; b <= factorsLessThanOrEqualTo; b++) {
                        int c = sumTo - a - b;
                        if (c > b && c <= factorsLessThanOrEqualTo) {
                            if (a * a + b * b == c * c) {
                                triplets.add(new PythagoreanTriplet(a, b, c));
                            }
                        }
                    }
                }
            }
            return triplets;
        }
    }
}