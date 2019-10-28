import java.util.*;

public class Teacher extends Person {
    List<Student> preferences = new ArrayList<>();
    List<Project> projects = new ArrayList<>();
    Map<Project, List<Student>> projectedPreferenceList;
    int capacity;

    /**
     * @param name
     * @param email
     */
    public Teacher(String name, String email, int _capacity) {
        super(name, email);
        this.capacity = _capacity;
    }

    public int getCapacity() {
        return capacity;
    }

    public Map<Project, List<Student>> getProjectedPreferenceList() {
        return projectedPreferenceList;

    }

    public void BuildProjectedPreferenceList() {
        projectedPreferenceList = new HashMap<Project, List<Student>>();

        for (Project project : projects) {
            for (Student student : preferences) {
                if (StudentPrefersProject(student, project)) {
                    if (projectedPreferenceList.containsKey(project)) {
                        projectedPreferenceList.get(project).add(student);
                    } else {
                        projectedPreferenceList.put(project, new ArrayList<>(Arrays.asList(student)));
                    }
                }
            }
        }
    }

    public boolean StudentPrefersProject(Student student, Project project) {
        for (Project studProject : student.getPreferences())
            if (studProject == project)
                return (true);
        return (false);
    }

    public List<Student> getPreferences() {
        return preferences;
    }

    /**
     * @param preferences
     */
    public void setPreferences(Student... preferences) {
        for (Student preference : preferences) {
            this.preferences.add(preference);
        }
    }

    /**
     * @param name
     * @param capacity
     * @return
     */
    public Project createProject(String name, int capacity) {
        Project p = new Project(name, capacity, this);
        this.projects.add(p);
        return (p);
    }

    public List<Project> getProjects() {
        return this.projects;
    }
}
