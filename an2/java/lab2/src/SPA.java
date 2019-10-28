import javafx.util.Pair;

import java.util.*;

public class SPA {
    private ArrayList<Student> Students = new ArrayList<>();
    private ArrayList<Teacher> Teachers = new ArrayList<>();
    private Map<Project, List<Student>> studentsForProject;
    private Map<Teacher, List<Student>> studentsForTeacher;
    private boolean studentIsFree[];
    private int nrProjects = 0;
//    Lkj = studentii preferati de teacher k care vor project j
//    Bk = studentii care prefera un proiect oferit de teacher k
//    M(Pj) = students assigned to project j
//    M(Lk) = students assigned to teacher k
//    M(Si) = project assigned to student i
//    A(i) = projects preffered by student i

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

        studentIsFree = new boolean[students.length];
        Arrays.fill(studentIsFree, true);
    }

    /**
     * add Teacher to Teachers list.
     *
     * @param teachers
     */
    public void setTeachers(Teacher... teachers) {
        for (Teacher teacher : teachers) {
            if (!Teachers.contains(teacher)) {
                Teachers.add(teacher);
                teacher.BuildProjectedPreferenceList();
            } else {
                System.out.println(teacher.getName() + " a fosst deja adaugat.");
            }
            nrProjects += teacher.getProjects().size();
        }
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
        Pair<Student, Project> inst;
        ArrayList<Pair<Student, Project>> ans = new ArrayList<>();
        studentsForTeacher = new HashMap<>();
        studentsForProject = new HashMap<>();
        Student freeStudent, worstStudent;
        Project firstPreferredProject, projectForWorstStudent;
        Teacher teacherWhoOffersProject;

        while (true) {
            freeStudent = SomeStudentIsFree();
            if (freeStudent == null) break;

            firstPreferredProject = FirstPreferredProject(freeStudent);
            teacherWhoOffersProject = TeacherWhoOffersProject(firstPreferredProject);
            if (teacherWhoOffersProject == null) {
                System.out.println("No teacher offers project with index " + firstPreferredProject.getIndex());
                break;
            }

            //provisionally assign student to project
            //and student to teacher
            inst = new Pair(freeStudent, firstPreferredProject);
            AddStudentToTeacher(freeStudent, teacherWhoOffersProject);
            AddStudentToProject(freeStudent, firstPreferredProject);
            ans.add(inst);
            studentIsFree[Students.indexOf(freeStudent)] = false;

            if (ProjectIsOverSubscribed(firstPreferredProject)) {
                //remove the worstStudent from the project firstPreferredProject
                worstStudent = WorstStudent(firstPreferredProject);
                RemoveFromList(ans, worstStudent, firstPreferredProject);
            } else if (TeacherIsOverSubscribed(teacherWhoOffersProject)) {
                worstStudent = WorstStudent(teacherWhoOffersProject);
                projectForWorstStudent = ProjectForStudent(worstStudent);
                RemoveFromList(ans, worstStudent, projectForWorstStudent);//modific si in studentIsFree
            }
            if (studentsForProject.get(firstPreferredProject).size() == firstPreferredProject.getCapacity()) {//project is full
                worstStudent = WorstStudent(firstPreferredProject);
                List<Student> successors = GetSuccessors(firstPreferredProject, worstStudent);
                if (successors != null) {
                    for (Student successor : successors) {
                        RemoveFromList(ans, successor, firstPreferredProject);//modific si in studentIsFree
                        successor.getPreferences().remove(firstPreferredProject);
                    }
                }
            }

            if (studentsForTeacher.get(teacherWhoOffersProject).size() == teacherWhoOffersProject.getCapacity()) {//teacher is full
                worstStudent = WorstStudent(teacherWhoOffersProject);
                List<Student> successors = GetSuccessors(teacherWhoOffersProject, worstStudent);
                List<Project> toRemove;
                for (Student successor : successors) {
                    toRemove = new ArrayList<>();
                    for (Project studProject : successor.getPreferences()) {
                        if (teacherWhoOffersProject.getProjects().contains(studProject)) {
                            RemoveFromList(ans, successor, studProject);//modific si in studentIsFree
                            toRemove.add(studProject);
                        }
                    }

                    for (Project project : toRemove) {
                        successor.getPreferences().remove(project);
                    }
                }
            }
        }
        return (ans);
    }

    private Project FirstPreferredProject(Student student) {
        return student.getPreferences().get(0);

        /*for (Project project : student.getPreferences()) {
            if (!studentsForProject.containsKey(project)) return project;
            if (project.getCapacity() > studentsForProject.get(project).size())
                return project;
        }

        if (student.getPreferences().size() > 0)
            return student.getPreferences().get(0);
        return (null);*/
    }

    private List<Student> GetSuccessors(Teacher teacher, Student student) {
        List<Student> rez = new ArrayList<>();
        int studIndex;

        studIndex = teacher.getPreferences().indexOf(student);
        for (int i = studIndex + 1; i < teacher.getPreferences().size(); ++i)
            rez.add(teacher.getPreferences().get(i));
        return (rez);
    }

    private List<Student> GetSuccessors(Project project, Student student) {
        List<Student> rez = new ArrayList<>();
        Teacher teacher = project.getTeacher();
        int studIndex;

        studIndex = teacher.getProjectedPreferenceList().get(project).indexOf(student);
        for (int i = studIndex + 1; i < teacher.getProjectedPreferenceList().get(project).size(); ++i)
            rez.add(teacher.getProjectedPreferenceList().get(project).get(i));
        return (rez);
    }

    private void RemoveFromList(List<Pair<Student, Project>> ans, Student student, Project project) {
        if (project == null || student == null) return;
        for (Pair<Student, Project> pair : ans)
            if (pair.getKey() == student && pair.getValue() == project) {
                ans.remove(pair);
                studentIsFree[Students.indexOf(student)] = true;
                studentsForProject.get(project).remove(student);
                studentsForTeacher.get(project.getTeacher()).remove(student);
                break;
            }
    }

    private Project ProjectForStudent(Student student) {
        for (Map.Entry<Project, List<Student>> m : studentsForProject.entrySet())
            if (m.getValue().contains(student))
                return (m.getKey());
        return (null);
    }

    private boolean TeacherIsOverSubscribed(Teacher teacher) {
        return (studentsForTeacher.get(teacher).size() > teacher.getCapacity());
    }

    private Student WorstStudent(Teacher teacher) {
        List<Student> students = teacher.getPreferences();
        for (Student student : studentsForTeacher.get(teacher)) {
            if (!students.contains(student))
                return (student);
        }

        for (int i = students.size() - 1; i >= 0; --i)
            if (studentsForTeacher.get(teacher).contains(students.get(i)))
                return (students.get(i));
        return (null);
    }

    private Student WorstStudent(Project project) {
        //aflu de cine e oferit proiectul asta
        Teacher teacher = project.getTeacher();
        //studentii preferati de el, studenti care prefera proiectul project
        List<Student> students;
        students = teacher.getProjectedPreferenceList().get(project);
        for (int i = students.size() - 1; i >= 0; --i) {
            if (studentsForProject.get(project).contains(students.get(i)))
                return students.get(i);
        }

//        if (studentsForProject.get(project).size() > 0)
//            return studentsForProject.get(project).get(studentsForProject.get(project).size() - 1);
        return (null);
    }

    private boolean ProjectIsOverSubscribed(Project project) {
        return (studentsForProject.get(project).size() > project.getCapacity());
    }

    private Teacher TeacherWhoOffersProject(Project project) {
        for (Teacher teacher : Teachers) {
            for (Project teacherProject : teacher.getProjects())
                if (project == teacherProject)
                    return teacher;
        }

        return null;
    }

    private Student SomeStudentIsFree() {
        for (int i = 0; i < studentIsFree.length; ++i)
            if (studentIsFree[i] && Students.get(i).getPreferences().size() > 0)
                return (Students.get(i));

        return null;
    }

    private void AddStudentToTeacher(Student student, Teacher teacher) {
        if (studentsForTeacher.containsKey(teacher)) {
            studentsForTeacher.get(teacher).add(student);
        } else {
            studentsForTeacher.put(teacher, new ArrayList<>(Arrays.asList(student)));
        }
    }

    private void AddStudentToProject(Student student, Project project) {
        if (studentsForProject.containsKey(project)) {
            studentsForProject.get(project).add(student);
        } else {
            studentsForProject.put(project, new ArrayList<>(Arrays.asList(student)));
        }
    }
}