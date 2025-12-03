import java.util.Objects;

public class Clock {
    private int hours;
    private int minutes;

    public Clock(int hours, int minutes) {
        this.hours = hours;
        this.minutes = minutes;
        adjustTime();
    }

    public void add(int minutes) {
        this.minutes += minutes;
        adjustTime();
    }

    @Override
    public String toString() {
        int h = hours;
        int m = minutes;

        return String.format("%02d:%02d", h, m);
    }

    @Override
    public boolean equals(Object o) {
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