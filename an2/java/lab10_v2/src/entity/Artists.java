package entity;

import javax.persistence.*;
import java.util.Collection;
import java.util.Objects;

@Entity
public class Artists {
    private long id;
    private String name;
    private String country;
    private Collection<Albums> albumsById;

    public Artists(String artistName) {
        this.name = artistName;
        this.country = "Romania";
    }

    public Artists() {
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
        return id == artists.id &&
                Objects.equals(name, artists.name) &&
                Objects.equals(country, artists.country);
    }

    @Override
    public int hashCode() {

        return Objects.hash(id, name, country);
    }

    @OneToMany(mappedBy = "artistsByArtistId")
    public Collection<Albums> getAlbumsById() {
        return albumsById;
    }

    public void setAlbumsById(Collection<Albums> albumsById) {
        this.albumsById = albumsById;
    }
}
