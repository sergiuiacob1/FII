import javafx.util.Pair;

import java.util.ArrayList;
/**
 * @author Ninicu Cristian, Sergiu Iacob
 */
public class classA {
    /**
     * Command line arguments.
     * @param args
     */
    public static void main(String[] args){
            Student s1 = new Student("S1", "s1@info.uaic.ro");
            Student s2 = new Student("S2", "s2@info.uaic.ro");
            Student s3 = new Student("S3", "s3@info.uaic.ro");
            Student s4 = new Student("S4", "s4@info.uaic.ro");
            Student s5 = new Student("S5", "s5@info.uaic.ro");
            Student s6 = new Student("S6", "s6@info.uaic.ro");
            Student s7 = new Student("S7", "s7@info.uaic.ro");

            Teacher t1 = new Teacher("T1", "t1@info.uaic.ro", 3);
            Teacher t2 = new Teacher("T2", "t2@info.uaic.ro", 2);
            Teacher t3 = new Teacher("T3", "t3@info.uaic.ro", 2);

            Project p1 = t1.createProject("P1", 2);
            Project p2 = t1.createProject("P2", 1);
            Project p3 = t1.createProject("P3", 1);
            Project p4 = t2.createProject("P4", 1);
            Project p5 = t2.createProject("P5", 1);
            Project p6 = t2.createProject("P6", 1);
            Project p7 = t3.createProject("P7", 1);
            Project p8 = t3.createProject("P8", 1);

            s1.setPreferences(p1, p7);
            s2.setPreferences(p1, p3, p3, p4, p5, p6);
            s3.setPreferences(p2, p1, p4);
            s4.setPreferences(p2);
            s5.setPreferences(p1, p2, p3, p4);
            s6.setPreferences(p2, p3, p4, p5, p6);
            s7.setPreferences(p5, p3, p8);

            t1.setPreferences(s7, s4, s1, s3, s2, s5, s6);
            t2.setPreferences(s3, s2, s6, s7, s5);
            t3.setPreferences(s1, s7);

            /*Problem problem = new Problem();
            problem.setStudents(s1, s2, s3, s4, s5, s6, s7);
            problem.setTeachers(t1, t2, t3);
            System.out.println(problem);
            ans = problem.solve();
            System.out.println("\nGreedy Solution: ");
            for(int i=0;i<ans.size();i++){
                System.out.println("\t\t\t" + ans.get(i).getKey().getName() + " -> " + ans.get(i).getValue().getName());
            }*/

            SPA problemSPA = new SPA();
            ArrayList<Pair<Student, Project>> ans;
            problemSPA.setStudents(s1, s2, s3, s4, s5, s6, s7);
            problemSPA.setTeachers(t1, t2, t3);
            System.out.println(problemSPA);
            ans = problemSPA.solve();
            System.out.println("\nSPA Solution: ");
            for(int i=0;i<ans.size();i++){
                    System.out.println("\t\t\t" + ans.get(i).getKey().getName() + " -> " + ans.get(i).getValue().getName());
            }
        }
}

