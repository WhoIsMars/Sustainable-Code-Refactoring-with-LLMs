import java.math.BigInteger;

class Grains {
    private static final BigInteger[] POWERS_OF_TWO = new BigInteger[65];
    private static final BigInteger TOTAL_GRAINS;
    
    static {
        POWERS_OF_TWO[0] = BigInteger.ONE;
        for (int i = 1; i < 65; i++) {
            POWERS_OF_TWO[i] = POWERS_OF_TWO[i - 1].shiftLeft(1);
        }
        TOTAL_GRAINS = POWERS_OF_TWO[64].subtract(BigInteger.ONE);
    }

    BigInteger grainsOnSquare(final int square) {
        if (square < 1 || square > 64) {
            throw new IllegalArgumentException("square must be between 1 and 64");
        }
        return POWERS_OF_TWO[square - 1];
    }

    BigInteger grainsOnBoard() {
        return TOTAL_GRAINS;
    }
}