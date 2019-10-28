public class Building extends Item implements Asset {
    int area = 0;

    Building(String name, int area, int price) {
        super(name, price);
        this.area = area;
    }

    @Override
    public int computeProfit() {
        return area / price * evaluateRisk();
    }
}
