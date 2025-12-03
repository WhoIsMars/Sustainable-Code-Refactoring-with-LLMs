import java.util.List;
import java.util.ArrayList;

class KindergartenGarden {

    private final Plant[][] plants;
    private final int plantRows;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        plantRows = rows.length;
        plants = new Plant[plantRows][];

        for (int i = 0; i < plantRows; i++) {
            String row = rows[i];
            plants[i] = new Plant[row.length()];
            for (int j = 0; j < row.length(); j++) {
                plants[i][j] = Plant.getPlant(row.charAt(j));
            }
        }
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        List<Plant> studentPlants = new ArrayList<>(4);

        for (int i = 0; i < plantRows; i++) {
            studentPlants.add(plants[i][studentIndex * 2]);
            studentPlants.add(plants[i][studentIndex * 2 + 1]);
        }

        return studentPlants;
    }
}