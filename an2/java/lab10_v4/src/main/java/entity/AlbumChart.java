package entity;

import javax.persistence.*;

@Entity
@Table(name = "ALBUM_CHART", schema = "STUDENT", catalog = "")
public class AlbumChart {
    private long id;
    private Album albumByIdAlbum;

    @Id
    @Column(name = "ID", nullable = false, precision = 0)
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AlbumChart that = (AlbumChart) o;

        if (id != that.id) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return (int) (id ^ (id >>> 32));
    }

    @ManyToOne
    @JoinColumn(name = "ID_ALBUM", referencedColumnName = "ID", nullable = false)
    public Album getAlbumByIdAlbum() {
        return albumByIdAlbum;
    }

    public void setAlbumByIdAlbum(Album albumByIdAlbum) {
        this.albumByIdAlbum = albumByIdAlbum;
    }
}
