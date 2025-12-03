import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class KindergartenGarden {
    private final String garden;
    private final int rowLength;
    private final Map<String, Integer> studentIndices = new HashMap<>();

    KindergartenGarden(String garden) {
        this.garden = garden.replace("\n", "");
        this.rowLength = this.garden.length() / 2;
        initializeStudentIndices();
    }

    private void initializeStudentIndices() {
        studentIndices.put("Alice", 0);
        studentIndices.put("Bob", 1);
        studentIndices.put("Charlie", 2);
        studentIndices.put("David", 3);
        studentIndices.put("Eve", 4);
        studentIndices.put("Fred", 5);
        studentIndices.put("Ginny", 6);
        studentIndices.put("Harriet", 7);
        studentIndices.put("Ileana", 8);
        studentIndices.put("Joseph", 9);
        studentIndices.put("Kincaid", 10);
        studentIndices.put("Larry", 11);
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = studentIndices.getOrDefault(student, -1);
        if (studentIndex == -1) {
            return new ArrayList<>();
        }

        int firstPlotIndex = studentIndex * 2;
        int secondPlotIndex = firstPlotIndex + 1;
        int thirdPlotIndex = firstPlotIndex + rowLength;
        int fourthPlotIndex = thirdPlotIndex + 1;

        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstPlotIndex)));
        plants.add(Plant.getPlant(garden.charAt(secondPlotIndex)));
        plants.add(Plant.getPlant(garden.charAt(thirdPlotIndex)));
        plants.add(Plant.getPlant(garden.charAt(fourthPlotIndex)));

        return plants;
    }
}