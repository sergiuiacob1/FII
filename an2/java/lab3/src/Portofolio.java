import java.util.ArrayList;

public class Portofolio {
    ArrayList<Asset> sol = new ArrayList<>();
    int weight = 0;
    int totalPrice = 0;

    public void computeWeight(){
        for(int i=0;i<sol.size();i++) {
            weight += sol.get(i).computeProfit();
            totalPrice += ((Item)sol.get(i)).price;
        }
    }

    @Override
    public String toString() {
        return "Portofolio{" +
                "sol=" + sol +
                ", weight=" + weight +
                ", totalPrice=" + totalPrice +
                '}';
    }
}
