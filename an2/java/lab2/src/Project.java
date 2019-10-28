public class Project {
    Teacher teacher;
    String name;
    int capacity;

    /**
     * @param name
     * @param capacity
     */
    Project(String name, int capacity, Teacher _teacher) {
        this.name = name;
        this.capacity = capacity;
        this.teacher = _teacher;
    }

    public Teacher getTeacher() {
        return teacher;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public int getIndex() {
        int result = 0;
        for (int i = 1; i < name.length(); ++i)
            result = result * 10 + (name.charAt(i) - '0');
        return result;
    }

    /**
     * Ovveriding toString method
     *
     * @return returns object in string format
     */
    @Override
    public String toString() {
        return "Project{" +
                "name='" + name + '\'' +
                ", capacity=" + capacity +
                '}';
    }
}
