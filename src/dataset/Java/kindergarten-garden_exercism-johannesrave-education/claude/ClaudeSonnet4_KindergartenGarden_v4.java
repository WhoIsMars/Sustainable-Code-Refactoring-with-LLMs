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
        int studentIndex = (student.charAt(0) - 'A') * 2;
        int firstRowStart = studentIndex;
        int firstRowEnd = studentIndex + 1;
        int secondRowStart = studentIndex + halfLength;
        int secondRowEnd = secondRowStart + 1;
        
        List<Plant> plants = new ArrayList<>(4);
        plants.add(Plant.getPlant(garden.charAt(firstRowStart)));
        plants.add(Plant.getPlant(garden.charAt(firstRowEnd)));
        plants.add(Plant.getPlant(garden.charAt(secondRowStart)));
        plants.add(Plant.getPlant(garden.charAt(secondRowEnd)));
        
        return plants;
    }

    private boolean isStudentsPlot(int plot, String student) {
        int fstRow = (student.charAt(0) - 'A') * 2;
        int sndRow = fstRow + halfLength;
        return (plot == fstRow || plot == fstRow+1 || plot == sndRow || plot == sndRow+1);
    }
}