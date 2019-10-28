import java.util.*;

public class AssetManager {
    ArrayList<Item> setOfItems = new ArrayList<>();
    ArrayList<Asset> setOfAssets = new ArrayList<>();

    public void add(Item...items){
        for(Item currentItem : items){
            setOfItems.add(currentItem);
            if(currentItem instanceof Asset){
                setOfAssets.add((Asset) currentItem);
            }
        }
    }

    public ArrayList<Item> getItems(){
        Collections.sort(setOfItems, new Comparators.MyNameComp());
        return(setOfItems);
    }

    public ArrayList<Asset> getAssets(){
        Collections.sort(setOfAssets, new Comparators.MyProfitComp());
        return(setOfAssets);
    }

    Portofolio createPortofolio(Algorithm algorithm, int maxValue){
        Portofolio ans = new Portofolio();
        ans.sol = algorithm.solve(setOfAssets, maxValue);
        ans.computeWeight();
        return(ans);
    }

}
