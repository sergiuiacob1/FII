package lab4;

import exceptions.FileNotFoundException;
import exceptions.InvalidYearException;

public class Book extends Document {

    Book(String name, String path, Integer year, String... authors) throws InvalidYearException, FileNotFoundException {
        super(name, path, year, authors);
    }

}
