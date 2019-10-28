import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Student extends Person {
    List<Project> preferences = new ArrayList<>();

    /**
     * @param name
     * @param email
     */
    public Student(String name, String email) {
        super(name, email);
    }

    public List<Project> getPreferences() {
        return preferences;
    }

    public void setPreferences(Project... preferences) {
        for (Project preference : preferences) {
            this.preferences.add(preference);
        }
    }
    //

    /**
     * My Comparator fro Student objects
     */
    static class MyComp implements Comparator<Student> {
        public int compare(Student a, Student b) {
            Integer x = a.preferences.size();
            Integer y = b.preferences.size();
            return x.compareTo(y);
        }
    }
}