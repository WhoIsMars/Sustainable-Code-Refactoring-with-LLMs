import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {
    private final String garden;
    private final int rowLength;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        this.garden = String.join("", rows);
        this.rowLength = this.garden.length() / 2;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = student.charAt(0) - 'A';
        int firstPlotIndex = studentIndex * 2;

        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstPlotIndex)));
        plants.add(Plant.getPlant(garden.charAt(firstPlotIndex + 1)));
        plants.add(Plant.getPlant(garden.charAt(firstPlotIndex + rowLength)));
        plants.add(Plant.getPlant(garden.charAt(firstPlotIndex + rowLength + 1)));

        return plants;
    }
}