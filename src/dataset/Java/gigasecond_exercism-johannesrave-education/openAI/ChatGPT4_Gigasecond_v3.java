import java.time.LocalDate;
import java.time.LocalDateTime;

public class Gigasecond {
    private static final long BILLION = 1_000_000_000L;
    private final LocalDateTime aLotLater;

    public Gigasecond(LocalDate moment) {
        this.aLotLater = moment.atStartOfDay().plusSeconds(BILLION);
    }

    public Gigasecond(LocalDateTime moment) {
        this.aLotLater = moment.plusSeconds(BILLION);
    }

    public LocalDateTime getDateTime() {
        return aLotLater;
    }
}