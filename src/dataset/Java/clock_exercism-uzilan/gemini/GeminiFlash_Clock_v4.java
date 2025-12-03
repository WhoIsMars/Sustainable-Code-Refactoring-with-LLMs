import java.util.Objects;

public class Clock {
    private int hours;
    private int minutes;

    public Clock(final int hours, final int minutes) {
        this.hours = hours;
        this.minutes = minutes;
        adjustTime();
    }

    public void add(final int minutes) {
        this.minutes += minutes;
        adjustTime();
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder(5);
        sb.append(String.format("%02d", hours));
        sb.append(':');
        sb.append(String.format("%02d", minutes));
        return sb.toString();
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Clock clock = (Clock) o;
        return hours == clock.hours && minutes == clock.minutes;
    }

    @Override
    public int hashCode() {
        return Objects.hash(hours, minutes);
    }

    private void adjustTime() {
        int totalMinutes = hours * 60 + minutes;
        totalMinutes %= 1440;
        if (totalMinutes < 0) {
            totalMinutes += 1440;
        }
        hours = totalMinutes / 60;
        minutes = totalMinutes % 60;
    }
}