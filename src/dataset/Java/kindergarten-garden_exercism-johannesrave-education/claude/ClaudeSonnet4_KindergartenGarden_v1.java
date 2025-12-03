import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {
    private final String garden;
    private final int halfLength;

    KindergartenGarden(String garden) {
        this.garden = garden.replace("\n", "");
        this.halfLength = this.garden.length() / 2;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = student.charAt(0) - 'A';
        int fstRow = studentIndex * 2;
        int sndRow = fstRow + halfLength;
        
        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(fstRow)));
        plants.add(Plant.getPlant(garden.charAt(fstRow + 1)));
        plants.add(Plant.getPlant(garden.charAt(sndRow)));
        plants.add(Plant.getPlant(garden.charAt(sndRow + 1)));
        
        return plants;
    }
}