package lab4;

public class SaveCommand {
    public void check(String[] arr) {
    }

    public void run(Catalog catalog, String[] arr) {
        catalog.save(arr[1]);
    }
}
