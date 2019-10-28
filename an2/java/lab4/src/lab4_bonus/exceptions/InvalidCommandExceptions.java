package exceptions;

public class InvalidCommandExceptions extends Exception {
    public InvalidCommandExceptions(String err){
        super(err);
    }
}
