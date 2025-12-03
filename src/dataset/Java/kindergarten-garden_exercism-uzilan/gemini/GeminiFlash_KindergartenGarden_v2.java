import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {

    private final List<Plant> plants;
    private final int rowLength;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        rowLength = rows[0].length();
        plants = new ArrayList<>();
        for (String row : rows) {
            for (int i = 0; i < row.length(); i++) {
                plants.add(Plant.getPlant(row.charAt(i)));
            }
        }
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        int startIndex = studentIndex * 2;
        List<Plant> studentPlants = new ArrayList<>(4);
        studentPlants.add(plants.get(startIndex));
        studentPlants.add(plants.get(startIndex + 1));
        studentPlants.add(plants.get(rowLength + startIndex));
        studentPlants.add(plants.get(rowLength + startIndex + 1));
        return studentPlants;
    }
}