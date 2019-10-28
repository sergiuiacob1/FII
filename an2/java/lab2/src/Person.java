public class Person {
    String name;
    String email;

    /**
     * @param name
     * @param email
     */
    Person(String name, String email) {
        this.name = name;
        this.email = email;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Overriding equals method
     *
     * @param obj
     * @return return true/false if they are equal/not equal.
     */
    @Override
    public boolean equals(Object obj) {
        if (obj == this)
            return (true);
        if (obj == null)
            return ((this == null));
        if (!(obj instanceof Person)) {
            return (false);
        }
        Person objPerson = (Person) obj;
        if (objPerson.getEmail() == this.name &&
                objPerson.getEmail() == this.email)
            return (true);
        return (false);
    }

    /**
     * Ovveriding toString method
     *
     * @return returns object in string format
     */
    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", email='" + email + '\'' +
                '}';
    }
}
