package exceptions;

public class InvalidYearException extends Exception {
    public InvalidYearException(String error) {
        super(error);
    }
}