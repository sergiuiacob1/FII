package lab4;

class InvalidCommandException extends Exception{
    public InvalidCommandException (String error){
        super (error);
    }
}
