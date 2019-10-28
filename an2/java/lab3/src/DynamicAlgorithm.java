import javafx.util.Pair;

import java.net.Inet4Address;
import java.util.ArrayList;
import java.util.List;

import static sun.swing.MenuItemLayoutHelper.max;

public class DynamicAlgorithm implements Algorithm {
    int value[] = new int[100];
    int weight[] = new int[100];
    int index[] = new int[100];
    @Override
    public ArrayList<Asset> solve(ArrayList<Asset> setOfItems, int maxValue) {
        ArrayList<Asset> ret = new ArrayList<>();
        int dp[][] = new int[100][100];
        for(int i=0;i<setOfItems.size();i++){
            weight[i + 1] = ((Item)setOfItems.get(i)).price;
            value[i + 1] = setOfItems.get(i).computeProfit();
            //index[i + 1] = i;
        }
        int n = setOfItems.size();
        int W = maxValue;
        for(int i=0;i<=n;i++) dp[i][0] = 0;
        for(int i=0;i<=W;i++) dp[0][i] = 0;

        for(int i=1;i<=n;i++){
            for(int w=1;w<=W;w++){
                if(weight[i] <= w){
                    if(value[i] + dp[i - 1][w - weight[i]] > dp[i - 1][w])
                            dp[i][w] = value[i] + dp[i - 1][w - weight[i]];
                    else
                            dp[i][w] = dp[i - 1][w];
                } else {
                    dp[i][w] = dp[i-1][w];
                }
            }
        }

        int i = n;
        int k = W;
        while(i > 0 && k > 0){
                if(dp[i][k] != dp[i-1][k]){
                    //System.out.println(i);
                    ret.add(setOfItems.get(i - 1));
                    k = k - weight[i];
                    i = i - 1;
                } else {
                    i = i - 1;
                }
        }
        return ret;
    }
}
