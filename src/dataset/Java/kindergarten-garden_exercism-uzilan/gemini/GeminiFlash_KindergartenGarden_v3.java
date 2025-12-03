import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {

    private final Plant[][] plants;
    private final int gardenWidth;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        int rowCount = rows.length;
        gardenWidth = rows[0].length();
        plants = new Plant[rowCount][gardenWidth];

        for (int i = 0; i < rowCount; i++) {
            String row = rows[i];
            for (int j = 0; j < gardenWidth; j++) {
                plants[i][j] = Plant.getPlant(row.charAt(j));
            }
        }
    }

    List<Plant> getPlantsOfStudent(String student) {
        final int studentIndex = student.charAt(0) - 'A';
        List<Plant> studentPlants = new ArrayList<>(4);
        int startIndex = studentIndex * 2;

        for (int i = 0; i < plants.length; i++) {
            studentPlants.add(plants[i][startIndex]);
            studentPlants.add(plants[i][startIndex + 1]);
        }

        return studentPlants;
    }
}