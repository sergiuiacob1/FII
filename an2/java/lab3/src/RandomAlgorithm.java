import java.util.ArrayList;
import java.util.HashMap;

public class RandomAlgorithm implements Algorithm {
    @Override
    public ArrayList<Asset> solve(ArrayList<Asset> setOfItems, int maxValue) {
        ArrayList<Asset> ret = new ArrayList<>();
        HashMap<Asset, Boolean> mp = new HashMap<>();
        int curr = 0;
        while(curr <= maxValue) {
            int k = (int) (Math.random() * setOfItems.size());
            if(mp.get(setOfItems.get(k)) != null) continue;
            if (curr + ((Item) setOfItems.get(k)).price <= maxValue) {
                curr += ((Item) setOfItems.get(k)).price;
                ret.add(setOfItems.get(k));
                mp.put(setOfItems.get(k), true);
            } else break;
        }
        return ret;
    }
}
