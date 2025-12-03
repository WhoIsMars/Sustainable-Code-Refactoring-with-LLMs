import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

class Gigasecond {

    private final LocalDateTime gigatime;
    private static final long GIGA_SECOND = 1_000_000_000L;

    Gigasecond(LocalDate birthDate) {
        this(birthDate.atStartOfDay());
    }

    Gigasecond(LocalDateTime birthDateTime) {
        this.gigatime = birthDateTime.plus(GIGA_SECOND, ChronoUnit.SECONDS);
    }

    LocalDateTime getDate() {
        return gigatime;
    }
}