package entity;

import javax.persistence.*;

@Entity
@Table(name = "ALBUMS_CHARTS", schema = "STUDENT")
public class AlbumsCharts {
    private long id;
    private long idAlbum;
    private long idChar;
    private Albums albumsByIdAlbum;
    private Charts chartsByIdChar;

    @Id
    @Column(name = "ID", nullable = false, precision = 0)
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Basic
    @Column(name = "ID_ALBUM", nullable = false, precision = 0)
    public long getIdAlbum() {
        return idAlbum;
    }

    public void setIdAlbum(long idAlbum) {
        this.idAlbum = idAlbum;
    }

    @Basic
    @Column(name = "ID_CHAR", nullable = false, precision = 0)
    public long getIdChar() {
        return idChar;
    }

    public void setIdChar(long idChar) {
        this.idChar = idChar;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AlbumsCharts that = (AlbumsCharts) o;

        if (id != that.id) return false;
        if (idAlbum != that.idAlbum) return false;
        if (idChar != that.idChar) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (int) (idAlbum ^ (idAlbum >>> 32));
        result = 31 * result + (int) (idChar ^ (idChar >>> 32));
        return result;
    }

    @ManyToOne
    @JoinColumn(name = "ID_ALBUM", referencedColumnName = "ID", nullable = false)
    public Albums getAlbumsByIdAlbum() {
        return albumsByIdAlbum;
    }

    public void setAlbumsByIdAlbum(Albums albumsByIdAlbum) {
        this.albumsByIdAlbum = albumsByIdAlbum;
    }

    @ManyToOne
    @JoinColumn(name = "ID_CHAR", referencedColumnName = "ID", nullable = false)
    public Charts getChartsByIdChar() {
        return chartsByIdChar;
    }

    public void setChartsByIdChar(Charts chartsByIdChar) {
        this.chartsByIdChar = chartsByIdChar;
    }
}
