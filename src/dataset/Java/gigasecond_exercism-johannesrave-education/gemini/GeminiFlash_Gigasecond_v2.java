import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

public class Gigasecond {
    static final private long BILLION = 1_000_000_000L;
    final private LocalDateTime alotLater;

    public Gigasecond(LocalDate moment) {
        this.alotLater = moment.atStartOfDay().plus(BILLION, ChronoUnit.SECONDS);
    }

    public Gigasecond(LocalDateTime moment) {
        this.alotLater = moment.plus(BILLION, ChronoUnit.SECONDS);
    }

    public LocalDateTime getDateTime() {
        return alotLater;
    }
}