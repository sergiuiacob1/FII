package entity;

import javax.persistence.*;

@Entity
@Table(name = "ALBUMS")
public class Album {
    private long id;
    private String name;
    private Long releaseYear;
    Artist artist;

    public Album() {
    }

    @Id
    @Column(name = "ID", nullable = false, precision = 0)
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Basic
    @Column(name = "NAME", nullable = false, length = 100)
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Basic
    @Column(name = "RELEASE_YEAR", nullable = true, precision = 0)
    public Long getReleaseYear() {
        return releaseYear;
    }

    public void setReleaseYear(Long releaseYear) {
        this.releaseYear = releaseYear;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Album albums = (Album) o;

        if (id != albums.id) return false;
        if (name != null ? !name.equals(albums.name) : albums.name != null) return false;
        if (releaseYear != null ? !releaseYear.equals(albums.releaseYear) : albums.releaseYear != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (releaseYear != null ? releaseYear.hashCode() : 0);
        return result;
    }

    public Album (String albumName, Artist artist){
        this.name = albumName;
        this.artist = artist;
    }
}
