package lab4;

import exceptions.FileNotFoundException;
import exceptions.InvalidYearException;

public class Article extends Document {

    Article(String name, String path, Integer year, String... authors) throws InvalidYearException, FileNotFoundException {
        super(name, path, year, authors);
    }
}
