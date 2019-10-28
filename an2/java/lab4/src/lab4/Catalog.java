package lab4;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Catalog implements java.io.Serializable {
    List<Document> documents;

    Catalog() {
        documents = new ArrayList<>();
    }

    public void add(Document document) {
        documents.add(document);
    }

    public void save(String path) {
        //serializare
        try {
            FileOutputStream fileOut = new FileOutputStream(path);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(this);
            out.close();
            fileOut.close();
            System.out.println("Wrote catalog in " + path);
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

    public static Catalog load(String path) {
        //deserializare
        Catalog rez = new Catalog();
        try {
            FileInputStream fileIn = new FileInputStream(path);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            rez = (Catalog) in.readObject();
            in.close();
            fileIn.close();
        } catch (IOException i) {
            i.printStackTrace();
            //return null;
        } catch (ClassNotFoundException c) {
            System.out.println("lab4.Catalog class not found");
            c.printStackTrace();
            //return null;
        }
        //this.documents = rez.documents;
        return rez;
    }

    public void list() {
        for (Document document : documents)
            System.out.println(document);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Catalog catalog = (Catalog) o;
        return Objects.equals(documents, catalog.documents);
    }

    @Override
    public int hashCode() {
        return Objects.hash(documents);
    }

    @Override
    public String toString() {
        return "lab4.Catalog{" +
                "documents=" + documents +
                '}';
    }

    public List<Document> getDocuments() {
        return documents;
    }

    public void setDocuments(List<Document> documents) {
        this.documents = documents;
    }
}
