import servlets.MyServlet;

public class Main {
    public static void main (String args[]){
        try {
            MyServlet myServlet = new MyServlet();
            myServlet.init();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
