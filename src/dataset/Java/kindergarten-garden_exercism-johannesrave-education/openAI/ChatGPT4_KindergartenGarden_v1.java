import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {
    private final String garden;
    private final int rowLength;

    KindergartenGarden(String garden) {
        this.garden = garden.replace("\n", "");
        this.rowLength = this.garden.length() / 2;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = (student.charAt(0) - 'A') * 2;
        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(studentIndex)));
        plants.add(Plant.getPlant(garden.charAt(studentIndex + 1)));
        plants.add(Plant.getPlant(garden.charAt(studentIndex + rowLength)));
        plants.add(Plant.getPlant(garden.charAt(studentIndex + rowLength + 1)));
        return plants;
    }
}