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
        int length = row.length();
        List<Plant> rowPlants = new ArrayList<>(length);
        for (int i = 0; i < length; i++) {
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
            result.add(row.get(startIndex));
            result.add(row.get(startIndex + 1));
        }
        return result;
    }
}