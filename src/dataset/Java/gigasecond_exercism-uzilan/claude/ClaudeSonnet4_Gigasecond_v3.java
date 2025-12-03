import java.time.LocalDate;
import java.time.LocalDateTime;

class Gigasecond {

    private static final long GIGASECOND = 1_000_000_000L;
    private final LocalDateTime gigatime;

    Gigasecond(LocalDate birthDate) {
        this.gigatime = birthDate.atStartOfDay().plusSeconds(GIGASECOND);
    }

    Gigasecond(LocalDateTime birthDateTime) {
        this.gigatime = birthDateTime.plusSeconds(GIGASECOND);
    }

    LocalDateTime getDate() {
        return gigatime;
    }
}