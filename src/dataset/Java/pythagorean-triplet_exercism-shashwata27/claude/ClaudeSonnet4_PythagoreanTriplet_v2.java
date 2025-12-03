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
        
        // Optimized bounds: a < b < c and a + b + c = sum
        // Since a < b < c, we have 3a < sum, so a < sum/3
        int maxA = this.sum / 3;
        
        for (int a = 3; a <= maxA; a++) {
            // For given a, we need b such that a < b and a + b + c = sum
            // Since b < c and a² + b² = c², we can derive better bounds
            int minB = a + 1;
            int maxB = (this.sum - a) / 2; // since b < c and b + c = sum - a
            
            for (int b = minB; b <= maxB; b++) {
                int c = this.sum - a - b;
                
                // Early termination: if c <= b, no valid triplets for larger b
                if (c <= b) break;
                
                // Check Pythagorean condition using multiplication to avoid overflow
                if (a * a + b * b == c * c) {
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
}