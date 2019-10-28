import java.util.Comparator;

public interface Asset {
    //final int financialRisk = 0;
    int computeProfit();
    default int evaluateRisk(){
        return(1);
    }
}
