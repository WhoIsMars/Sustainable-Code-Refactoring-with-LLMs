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
        if (sum <= 0 || factor <= 0) {
            return Collections.emptyList();
        }
        List<PythagoreanTriplet> triplets = new ArrayList<>();
        for (int a = 1; a <= factor / 3; a++) {
            for (int b = a + 1; b <= factor / 2; b++) {
                int c = sum - a - b;
                if (c > b && c <= factor && isValidTriplet(a, b, c)) {
                    triplets.add(new PythagoreanTriplet(a, b, c));
                }
            }
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
        int result = a;
        result = 31 * result + b;
        result = 31 * result + c;
        return result;
    }
}