import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {

    private final Plant[][] plants;
    private static final int STUDENTS = 12;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        plants = new Plant[2][STUDENTS * 2];

        for (int i = 0; i < 2; i++) {
            String row = rows[i];
            for (int j = 0; j < row.length(); j++) {
                plants[i][j] = Plant.getPlant(row.charAt(j));
            }
        }
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        List<Plant> studentPlants = new ArrayList<>(4);

        studentPlants.add(plants[0][studentIndex * 2]);
        studentPlants.add(plants[0][studentIndex * 2 + 1]);
        studentPlants.add(plants[1][studentIndex * 2]);
        studentPlants.add(plants[1][studentIndex * 2 + 1]);

        return studentPlants;
    }
}