public class Vehicle extends Item implements Asset {
    int performance = 0;


    Vehicle(String name, int performance, int price){
        super(name, price);
        this.performance = performance;
    }

    @Override
    public int computeProfit() {
        return performance / price * evaluateRisk();
    }
}
