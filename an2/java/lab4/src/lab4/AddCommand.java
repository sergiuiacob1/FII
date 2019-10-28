package lab4;

public class AddCommand {

    AddCommand() {

    }

    public void check(String type, String[] all) {

    }

    public void run(Catalog catalog, String type, String[] all) {
        if (type.compareTo("book") == 0) {
            String[] authors = new String[all.length - 4];
            for (int i = 4; i < all.length; i++)
                authors[i - 4] = all[i];
            Document doc;
            try {
                doc = new Book(all[1], all[2], Integer.parseInt(all[3]), authors);
            } catch (InvalidYearException e) {
                System.out.println("wrong year");
                return;
            } catch (FileNotFoundException e) {
                System.out.println("wrong path");
                return;
            }
            catalog.add(doc);
        }
        if (type.compareTo("article") == 0) {
            String[] authors = new String[all.length - 4];
            for (int i = 4; i < all.length; i++)
                authors[i - 4] = all[i];
            Document doc;
            try {
                doc = new Article(all[1], all[2], Integer.parseInt(all[3]), authors);
            } catch (InvalidYearException e) {
                System.out.println("wrong year");
                return;
            } catch (FileNotFoundException e) {
                System.out.println("wrong path");
                return;
            }
            catalog.add(doc);
        }
        if (type.compareTo("manual") == 0) {
            Document doc;
            try {
                doc = new Manual(all[1], all[2]);
            } catch (InvalidYearException e) {
                System.out.println("wrong year");
                return;
            } catch (FileNotFoundException e) {
                System.out.println("wrong path");
                return;
            }
            catalog.add(doc);
        }
    }
}
