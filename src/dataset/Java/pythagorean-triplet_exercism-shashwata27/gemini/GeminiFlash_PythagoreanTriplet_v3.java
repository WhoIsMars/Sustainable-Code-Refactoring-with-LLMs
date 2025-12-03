import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class PythagoreanTriplet {
    public int a, b, c;
    private int factor, sum;

    private PythagoreanTriplet() {
    }

    public PythagoreanTriplet(int a, int b, int c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public static PythagoreanTriplet makeTripletsList() {
        return new PythagoreanTriplet();
    }

    public PythagoreanTriplet withFactorsLessThanOrEqualTo(int factor) {
        this.factor = factor;
        return this;
    }

    public PythagoreanTriplet thatSumTo(int sum) {
        this.sum = sum;
        return this;
    }

    public List<PythagoreanTriplet> build() {
        if (sum <= 0) {
            return Collections.emptyList();
        }

        List<PythagoreanTriplet> triplets = new ArrayList<>();
        for (int a = 1; a < sum / 2; a++) {
            for (int b = a + 1; b < sum; b++) {
                int c = sum - a - b;
                if (c <= b) {
                    break;
                }

                if (isValidTriplet(a, b, c) && (factor == 0 || (a <= factor && b <= factor && c <= factor))) {
                    triplets.add(new PythagoreanTriplet(a, b, c));
                }
            }
        }

        if (triplets.isEmpty()) {
            return Collections.emptyList();
        }

        return triplets;
    }

    private boolean isValidTriplet(int a, int b, int c) {
        return a * a + b * b == c * c;
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
        int result = 17;
        result = 31 * result + a;
        result = 31 * result + b;
        result = 31 * result + c;
        return result;
    }
}