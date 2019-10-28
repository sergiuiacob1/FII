import javafx.util.Pair;

import java.util.*;

public class Problem {
    ArrayList<Student> Students = new ArrayList<>();
    ArrayList<Teacher> Teachers = new ArrayList<>();

    public ArrayList<Student> getStudents() {
        return Students;
    }

    /**
     * add Student to Students list.
     *
     * @param students
     */
    public void setStudents(Student... students) {
        for (Student student : students) {
            if (!Students.contains(student))
                Students.add(student);
            else {
                System.out.println(student.getName() + " a fost deja adaugat.");
            }
        }
    }

    public ArrayList<Teacher> getTeachers() {
        return Teachers;
    }

    /**
     * add Teacher to Teachers list.
     *
     *
     * @param teachers
     */
    public void setTeachers(Teacher... teachers) {
        for (Teacher teacher : teachers) {
            if (!Teachers.contains(teacher))
                Teachers.add(teacher);
            else {
                System.out.println(teacher.getName() + " a fosst deja adaugat.");
            }
        }
        ;
    }

    /**
     * @return returns list of all participants.
     */
    public ArrayList<Person> getParticipants() {
        ArrayList<Person> Persons = new ArrayList<>();
        for (int i = 0; i < Students.size(); i++) {
            Persons.add(Students.get(i));
        }
        for (int i = 0; i < Teachers.size(); i++) {
            Persons.add(Teachers.get(i));
        }
        return Persons;
    }

    /**
     * Ovveriding toString method
     *
     * @return returns object in string format
     */
    @Override
    public String toString() {
        return "Problem{" +
                "Students=" + Students +
                ", Teachers=" + Teachers +
                '}';
    }

    /**
     * @return matching for Problem instance
     */
    public ArrayList<Pair<Student, Project>> solve() {
        ArrayList<Pair<Student, Project>> ans = new ArrayList<>();
        Collections.sort(Students, new Student.MyComp());
        for (int i = 0; i < Students.size(); i++) {
            Pair<Student, Project> inst = null;
            for (int j = 0; j < Students.get(i).preferences.size(); j++) {
                if (Students.get(i).preferences.get(j).capacity > 0) {
                    inst = new Pair(Students.get(i), Students.get(i).preferences.get(j));
                    Students.get(i).preferences.get(j).capacity--;
                    break;
                }
            }
            ans.add(inst);
        }
        return (ans);
    }
}