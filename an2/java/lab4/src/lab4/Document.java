package lab4;

import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.Year;
import java.util.ArrayList;
import java.util.List;

public abstract class Document implements java.io.Serializable {
    protected String name, path;
    protected List<String> authors;
    protected Integer year;

    Document(String name, String path, Integer year, String... authors) throws InvalidYearException, FileNotFoundException {
        this.name = name;
        this.authors = new ArrayList<>();
        for (String author :
                authors) {
            this.authors.add(author);
        }

        this.setPath(path);
        this.setYear(year);
    }

    public void open() throws IOException {
        Desktop desktop = Desktop.getDesktop();
        desktop.open(new File(this.path));
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) throws FileNotFoundException {
        if (Files.notExists(Paths.get(path))) {
            throw new FileNotFoundException(path + " doesn't exist");
        } else {
            this.path = path;
        }
    }

    public List<String> getAuthors() {
        return authors;
    }

    public void setAuthors(List<String> authors) {
        this.authors = authors;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(int year) throws InvalidYearException {
        if (year > Year.now().getValue()) {
            throw new InvalidYearException("invalid year");
        } else {
            this.year = year;
        }
    }

    @Override
    public String toString() {
        return "lab4.Document{" +
                "name='" + name + '\'' +
                ", path='" + path + '\'' +
                ", authors=" + authors +
                ", year=" + year +
                '}';
    }
}
