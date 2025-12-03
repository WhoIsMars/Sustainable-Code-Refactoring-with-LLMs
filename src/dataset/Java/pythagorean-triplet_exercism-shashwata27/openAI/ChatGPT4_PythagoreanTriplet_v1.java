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
        List<PythagoreanTriplet> triplets = new ArrayList<>();
        int limit = Math.min(this.sum / 2, this.factor);
        for (int a = 1; a < limit; a++) {
            for (int b = a + 1; b < limit; b++) {
                int c = this.sum - a - b;
                if (c > b && c <= this.factor && isValidTriplet(a, b, c)) {
                    triplets.add(new PythagoreanTriplet(a, b, c));
                }
            }
        }
        return triplets.isEmpty() ? Collections.emptyList() : triplets;
    }

    private boolean isValidTriplet(int a, int b, int c) {
        return a * a + b * b == c * c;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o instanceof PythagoreanTriplet) {
            PythagoreanTriplet other = (PythagoreanTriplet) o;
            return this.a == other.a && this.b == other.b && this.c == other.c;
        }
        return false;
    }

    @Override
    public int hashCode() {
        int result = Integer.hashCode(a);
        result = 31 * result + Integer.hashCode(b);
        result = 31 * result + Integer.hashCode(c);
        return result;
    }
}