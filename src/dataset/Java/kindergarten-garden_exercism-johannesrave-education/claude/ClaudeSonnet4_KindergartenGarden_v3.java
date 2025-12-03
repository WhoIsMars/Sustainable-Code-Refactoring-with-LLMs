import java.util.List;
import java.util.ArrayList;

class KindergartenGarden {
    private final String garden;
    private final int halfLength;

    KindergartenGarden(String garden) {
        this.garden = garden.replace("\n", "");
        this.halfLength = this.garden.length() / 2;
    }

    List<Plant> getPlantsOfStudent(String student) {
        int studentIndex = student.charAt(0) - 'A';
        int firstRowStart = studentIndex * 2;
        int secondRowStart = firstRowStart + halfLength;
        
        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstRowStart)));
        plants.add(Plant.getPlant(garden.charAt(firstRowStart + 1)));
        plants.add(Plant.getPlant(garden.charAt(secondRowStart)));
        plants.add(Plant.getPlant(garden.charAt(secondRowStart + 1)));
        
        return plants;
    }

    private boolean isStudentsPlot(int plot, String student) {
        int studentIndex = student.charAt(0) - 'A';
        int firstRowStart = studentIndex * 2;
        int secondRowStart = firstRowStart + halfLength;
        return (plot == firstRowStart || plot == firstRowStart + 1 || 
                plot == secondRowStart || plot == secondRowStart + 1);
    }
}