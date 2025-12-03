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
        
        // Early termination if sum is too small for any valid triplet
        if (this.sum < 12) {
            return Collections.emptyList();
        }
        
        int maxA = this.sum / 3;
        for (int a = 3; a <= maxA; a++) {
            int maxB = (this.sum - a) / 2;
            for (int b = a; b <= maxB; b++) {
                int c = this.sum - a - b;
                if (c > b && a * a + b * b == c * c) {
                    triplets.add(new PythagoreanTriplet(a, b, c));
                }
            }
        }
        
        return triplets.isEmpty() ? Collections.emptyList() : triplets;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof PythagoreanTriplet)) return false;
        PythagoreanTriplet that = (PythagoreanTriplet) o;
        return this.a == that.a && this.b == that.b && this.c == that.c;
    }

    @Override
    public int hashCode() {
        return 31 * (31 * a + b) + c;
    }
}