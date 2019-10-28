package entity;

import javax.persistence.*;
import java.util.Collection;

@Entity
public class Albums {
    private long id;
    private String name;
    private long artistId;
    private Long releaseYear;
    private Artists artistsByArtistId;
    private Collection<AlbumsCharts> albumsChartsById;

    public Albums(String albumName, Artists artistFromDatabase) {
    }

    public Albums() {
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
    @Column(name = "ARTIST_ID", nullable = false, precision = 0)
    public long getArtistId() {
        return artistId;
    }

    public void setArtistId(long artistId) {
        this.artistId = artistId;
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

        Albums albums = (Albums) o;

        if (id != albums.id) return false;
        if (artistId != albums.artistId) return false;
        if (name != null ? !name.equals(albums.name) : albums.name != null) return false;
        if (releaseYear != null ? !releaseYear.equals(albums.releaseYear) : albums.releaseYear != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (int) (artistId ^ (artistId >>> 32));
        result = 31 * result + (releaseYear != null ? releaseYear.hashCode() : 0);
        return result;
    }

    @ManyToOne
    @JoinColumn(name = "ARTIST_ID", referencedColumnName = "ID", nullable = false)
    public Artists getArtistsByArtistId() {
        return artistsByArtistId;
    }

    public void setArtistsByArtistId(Artists artistsByArtistId) {
        this.artistsByArtistId = artistsByArtistId;
    }

    @OneToMany(mappedBy = "albumsByIdAlbum")
    public Collection<AlbumsCharts> getAlbumsChartsById() {
        return albumsChartsById;
    }

    public void setAlbumsChartsById(Collection<AlbumsCharts> albumsChartsById) {
        this.albumsChartsById = albumsChartsById;
    }
}
