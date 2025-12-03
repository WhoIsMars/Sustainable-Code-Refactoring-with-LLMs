import java.util.List;
import java.util.ArrayList;

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
        List<Plant> rowPlants = new ArrayList<>(row.length());
        for (int i = 0; i < row.length(); i++) {
            rowPlants.add(Plant.getPlant(row.charAt(i)));
        }
        return rowPlants;
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        final int startIndex = studentIndex * 2;
        final int endIndex = startIndex + 2;
        
        List<Plant> result = new ArrayList<>(plants.size() * 2);
        for (List<Plant> row : plants) {
            for (int i = startIndex; i < endIndex; i++) {
                result.add(row.get(i));
            }
        }
        return result;
    }
}