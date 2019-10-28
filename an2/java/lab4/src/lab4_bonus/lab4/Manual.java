package lab4;

import exceptions.FileNotFoundException;
import exceptions.InvalidYearException;

public class Manual extends Document{

    Manual (String name, String path) throws InvalidYearException, FileNotFoundException {
        super (name, path, 0);
    }
}
