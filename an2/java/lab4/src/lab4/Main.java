package lab4;

import java.io.IOException;
import java.util.InvalidPropertiesFormatException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException, InvalidCommandExceptions {
        //Compulsory
        /*
        lab4.Catalog catalog = new lab4.Catalog();
        try {
            catalog.add(new lab4.Book("The Art of Computer Programming", "fisier.txt", 1967, "Donald E. Knuth"));
            catalog.add(new lab4.Article("Mastering the Game of Go without Human Knowledge", "fisier.txt", 2017, "David Silver", "Julian Schrittwieser", "Karen Simonyan"));
            catalog.add(new lab4.Manual("Cookbook", "fisier.txt"));

        } catch (InvalidYearException e) {
            System.out.println("wrong year");
            return;
        } catch (FileNotFoundException e) {
            System.out.println("wrong path");
            return;
        }
        catalog.save("catalog.dat");
        //...
        catalog = lab4.Catalog.load("catalog.dat");
        catalog.list();
        */

        //Optional
        Catalog catalog = new Catalog();
        boolean notQuit = true;
        while (notQuit) {
            try {
                String str = new String();
                Scanner scanner = new Scanner(System.in);
                String command = new String();
                String type = new String();
                command = scanner.next();
                if (command.compareTo("add") == 0)
                    type = scanner.next();
                if (command.compareTo("quit") == 0) {
                    notQuit = false;
                    break;
                }
                str = scanner.nextLine();
                str = str.replace(" ", "");
                String[] arr = str.split("\"*\"");
                //
                if(command.compareTo("report") == 0){
                    ReportHtml report = new ReportHtml();
                    report.run(catalog);
                   // Document doc = new Document("html", "index.html", "1990", "");
                   // doc.open();

                } else if (command.compareTo("add") == 0) {
                    //book
                    //article
                    //manual
                    AddCommand addCommand = new AddCommand();
                    addCommand.run(catalog, type, arr);
                } else if (command.compareTo("load") == 0) {
                    //catalog
                    System.out.println(arr[1]);
                    String str1 = arr[1];
                    catalog = Catalog.load(str1);
                    //catalog.list();
                } else if (command.compareTo("list") == 0) {
                    //catalog
                    //catalog.list();
                    ListCommand listCommand = new ListCommand();
                    listCommand.run(catalog, arr);
                } else if (command.compareTo("save") == 0) {
                    //toCatalog
                    SaveCommand saveCommand = new SaveCommand();
                    saveCommand.run(catalog, arr);
                } else if (command.compareTo("play") == 0) {
                    //file
                    PlayCommand playCommand = new PlayCommand();
                    try {
                        playCommand.run(arr[1]);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else throw (new InvalidCommandExceptions("Comanda invalida"));
            } catch (InvalidCommandExceptions err) {
                System.out.println(err.getMessage());
                continue;
            }
        }

    }
}

