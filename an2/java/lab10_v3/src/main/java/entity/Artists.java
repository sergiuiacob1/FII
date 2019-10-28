package entity;

import javax.persistence.*;
import java.util.Collection;

@Entity
public class Artists {
    private long id;
    private String name;
    private String country;
    private Collection<Albums> albumsById;

    public Artists(String artistName) {
    }

    public Artists(){

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
    @Column(name = "COUNTRY", nullable = true, length = 100)
    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Artists artists = (Artists) o;

        if (id != artists.id) return false;
        if (name != null ? !name.equals(artists.name) : artists.name != null) return false;
        if (country != null ? !country.equals(artists.country) : artists.country != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (country != null ? country.hashCode() : 0);
        return result;
    }

    @OneToMany(mappedBy = "artistsByArtistId")
    public Collection<Albums> getAlbumsById() {
        return albumsById;
    }

    public void setAlbumsById(Collection<Albums> albumsById) {
        this.albumsById = albumsById;
    }
}
