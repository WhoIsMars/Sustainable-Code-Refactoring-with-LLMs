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
        int firstRowStart = studentIndex;
        int secondRowStart = studentIndex + rowLength;
        
        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstRowStart)));
        plants.add(Plant.getPlant(garden.charAt(firstRowStart + 1)));
        plants.add(Plant.getPlant(garden.charAt(secondRowStart)));
        plants.add(Plant.getPlant(garden.charAt(secondRowStart + 1)));
        
        return plants;
    }
}