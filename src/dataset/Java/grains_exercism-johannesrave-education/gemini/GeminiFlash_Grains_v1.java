import java.math.BigInteger;

class Grains {

    private static final BigInteger TWO = BigInteger.valueOf(2);

    BigInteger grainsOnSquare(final int square) {
        if (square < 1 || square > 64) {
            throw new IllegalArgumentException("square must be between 1 and 64");
        }
        return TWO.pow(square - 1);
    }

    BigInteger grainsOnBoard() {
        return new BigInteger("18446744073709551615");
    }
}