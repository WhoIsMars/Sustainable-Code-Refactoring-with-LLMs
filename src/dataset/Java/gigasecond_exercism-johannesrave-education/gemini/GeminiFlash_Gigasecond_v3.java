import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Duration;

public class Gigasecond {
    private static final Duration GIGASECOND = Duration.ofSeconds(1_000_000_000L);
    private final LocalDateTime alotLater;

    public Gigasecond(LocalDate moment) {
        this(moment.atStartOfDay());
    }

    public Gigasecond(LocalDateTime moment) {
        this.alotLater = moment.plus(GIGASECOND);
    }

    public LocalDateTime getDateTime() {
        return alotLater;
    }
}