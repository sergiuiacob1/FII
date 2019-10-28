import java.util.Comparator;
public class Comparators {

        static class MyNameComp implements Comparator<Item> {
            public int compare(Item a, Item b){
                return a.name.compareTo(b.name);
            }

        }

        static class MyProfitComp implements Comparator<Asset> {
            public int compare(Asset a, Asset b){
                Integer a1 = a.computeProfit();
                Integer b1 = b.computeProfit();
                return a1.compareTo(b1);
            }

        }

        static class MyRatioComp implements Comparator<Asset> {
            public int compare(Asset a, Asset b){
                float a1 = ((Item) a).price / a.computeProfit();
                float b1 = ((Item) b).price / b.computeProfit();
                return Float.compare(a1, b1);
            }

        }

}
