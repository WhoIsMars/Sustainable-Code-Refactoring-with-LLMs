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
        int maxA = sum / 3;
        
        for (int a = 3; a <= maxA; a++) {
            int maxB = (sum - a) / 2;
            for (int b = a; b <= maxB; b++) {
                int c = sum - a - b;
                if (c > b && a * a + b * b == c * c) {
                    triplets.add(new PythagoreanTriplet(a, b, c));
                }
            }
        }
        
        return triplets;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof PythagoreanTriplet)) return false;
        PythagoreanTriplet that = (PythagoreanTriplet) o;
        return a == that.a && b == that.b && c == that.c;
    }

    @Override
    public int hashCode() {
        return 31 * (31 * a + b) + c;
    }
}