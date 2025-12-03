import java.util.List;
import java.util.ArrayList;

class KindergartenGarden {

    private final List<Plant>[] plants;
    private final int numRows;

    @SuppressWarnings("unchecked")
    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        this.numRows = rows.length;
        this.plants = new List[numRows];
        
        for (int i = 0; i < numRows; i++) {
            plants[i] = parseRow(rows[i]);
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
        
        List<Plant> result = new ArrayList<>(numRows * 2);
        for (int i = 0; i < numRows; i++) {
            List<Plant> row = plants[i];
            for (int j = startIndex; j < endIndex && j < row.size(); j++) {
                result.add(row.get(j));
            }
        }
        return result;
    }
}