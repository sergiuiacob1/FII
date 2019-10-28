import com.sun.prism.GraphicsResource;

public class classA {
    public static void main(String[] args) {
        Building h1 = new Building("House 1", 27, 9);
        Building h2 = new Building("House 2", 27, 9);
        Building h3 = new Building("House 3", 64, 16);
        Vehicle c1 = new Vehicle("Car 1", 8, 4);
        Vehicle c2 = new Vehicle("Car 2", 8, 4);
        //Vehicle c3 = new Vehicle("Car 3", 8, 8);
        Jewel r1 = new Jewel("Ring 1", 2);
        AssetManager manager = new AssetManager();
        manager.add(h1, h2, h3);
        manager.add(c1, c2);
        manager.add(r1);
        System.out.println("Items sorted by name : " + manager.getItems());
        //-----------------------------------------------------------------
        System.out.println("Items sorted by profit : " + manager.getAssets());

        int maxValue = 20;
        Portofolio greedy = manager.createPortofolio(new GreedyAlgorithm(), maxValue);
        System.out.println("The best portofolio (greedy) is : " + greedy);

        Portofolio random = manager.createPortofolio(new RandomAlgorithm(), maxValue);
        System.out.println("The best portofolio (random) is : " + random);

        Portofolio dynamic = manager.createPortofolio(new DynamicAlgorithm(), maxValue);
        System.out.println("The best portofolio (dynamic) is : " + dynamic);

    }
}
