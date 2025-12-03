import java.util.ArrayList;
import java.util.List;

class KindergartenGarden {
    private final String garden;
    private final int rowLength;

    KindergartenGarden(String garden) {
        String[] rows = garden.split("\n");
        this.garden = String.join("", rows);
        this.rowLength = this.garden.length() / 2;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = student.charAt(0) - 'A';
        int firstPlot = studentIndex * 2;
        int secondPlot = firstPlot + 1;
        int thirdPlot = firstPlot + rowLength;
        int fourthPlot = thirdPlot + 1;

        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstPlot)));
        plants.add(Plant.getPlant(garden.charAt(secondPlot)));
        plants.add(Plant.getPlant(garden.charAt(thirdPlot)));
        plants.add(Plant.getPlant(garden.charAt(fourthPlot)));

        return plants;
    }
}