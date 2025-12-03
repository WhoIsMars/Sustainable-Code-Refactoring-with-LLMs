import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {

    private final List<Plant[]> plants;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        plants = new ArrayList<>(rows.length);
        for (String row : rows) {
            plants.add(parseRow(row));
        }
    }

    private Plant[] parseRow(String row) {
        int length = row.length();
        Plant[] rowPlants = new Plant[length];
        for (int i = 0; i < length; i++) {
            rowPlants[i] = Plant.getPlant(row.charAt(i));
        }
        return rowPlants;
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        final int startIndex = studentIndex * 2;
        final int endIndex = startIndex + 2;
        
        List<Plant> result = new ArrayList<>(plants.size() * 2);
        for (Plant[] row : plants) {
            result.add(row[startIndex]);
            result.add(row[endIndex]);
        }
        return result;
    }
}