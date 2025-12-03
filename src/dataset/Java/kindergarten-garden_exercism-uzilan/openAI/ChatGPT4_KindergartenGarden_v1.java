import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {

    private final List<List<Plant>> plants;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        plants = new ArrayList<>(rows.length);
        for (String row : rows) {
            plants.add(parseRow(row));
        }
    }

    private List<Plant> parseRow(String row) {
        List<Plant> plantRow = new ArrayList<>(row.length());
        for (int i = 0; i < row.length(); i++) {
            plantRow.add(Plant.getPlant(row.charAt(i)));
        }
        return plantRow;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = (student.charAt(0) - 'A') * 2;
        List<Plant> studentPlants = new ArrayList<>(plants.size() * 2);
        for (List<Plant> row : plants) {
            studentPlants.add(row.get(studentIndex));
            studentPlants.add(row.get(studentIndex + 1));
        }
        return studentPlants;
    }
}