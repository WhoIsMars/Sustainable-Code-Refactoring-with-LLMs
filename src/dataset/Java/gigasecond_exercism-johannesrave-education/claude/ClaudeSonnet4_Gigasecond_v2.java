import java.time.LocalDate;
import java.time.LocalDateTime;

public class Gigasecond {
    static final private long BILLION = 1_000_000_000L;
    final private LocalDateTime alotLater;

    public Gigasecond(LocalDate moment) {
        this.alotLater = moment.atStartOfDay().plusSeconds(BILLION);
    }

    public Gigasecond(LocalDateTime moment) {
        this.alotLater = moment.plusSeconds(BILLION);
    }

    public LocalDateTime getDateTime() {
        return alotLater;
    }
}