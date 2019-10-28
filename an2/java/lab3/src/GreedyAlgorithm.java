import java.util.ArrayList;
import java.util.Collections;

public class GreedyAlgorithm implements Algorithm {
    @Override
    public ArrayList<Asset> solve(ArrayList<Asset> setOfAsset, int maxValue) {
        ArrayList<Asset> ret = new ArrayList<>();
        Collections.sort(setOfAsset, new Comparators.MyRatioComp());
        int curr = 0;
        for(int i=0;i<setOfAsset.size(); i++){
            //System.out.println(setOfAsset.get(i) + " - " + setOfAsset.get(i).computeProfit());
            if(curr + ((Item)setOfAsset.get(i)).price <= maxValue){
                curr += ((Item)setOfAsset.get(i)).price;
                ret.add(setOfAsset.get(i));
            } else break;
        }
        return(ret);
    }

}
