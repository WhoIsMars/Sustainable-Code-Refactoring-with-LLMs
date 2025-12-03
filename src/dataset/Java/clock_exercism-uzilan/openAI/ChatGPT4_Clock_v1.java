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
        return String.format("%02d:%02d", hours, minutes);
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o) return true;
        if (!(o instanceof Clock)) return false;
        final Clock clock = (Clock) o;
        return hours == clock.hours && minutes == clock.minutes;
    }

    @Override
    public int hashCode() {
        return (hours * 60) + minutes;
    }

    private void adjustTime() {
        int totalMinutes = (hours * 60 + minutes) % (24 * 60);
        if (totalMinutes < 0) totalMinutes += 24 * 60;
        hours = totalMinutes / 60;
        minutes = totalMinutes % 60;
    }
}