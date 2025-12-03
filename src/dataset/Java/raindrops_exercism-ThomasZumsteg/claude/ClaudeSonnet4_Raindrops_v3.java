public class Raindrops {
    static String convert(Integer num) {
        StringBuilder sounds = new StringBuilder(15);
        boolean hasSound = false;
        
        if (num % 3 == 0) {
            sounds.append("Pling");
            hasSound = true;
        }
        if (num % 5 == 0) {
            sounds.append("Plang");
            hasSound = true;
        }
        if (num % 7 == 0) {
            sounds.append("Plong");
            hasSound = true;
        }
        
        return hasSound ? sounds.toString() : num.toString();
    }
}