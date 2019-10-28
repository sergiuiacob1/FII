package entity;

import javax.persistence.*;
import java.util.Collection;

@Entity
public class Charts {
    private long id;
    private String name;
    private Collection<AlbumsCharts> albumsChartsById;

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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Charts charts = (Charts) o;

        if (id != charts.id) return false;
        if (name != null ? !name.equals(charts.name) : charts.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        return result;
    }

    @OneToMany(mappedBy = "chartsByIdChar")
    public Collection<AlbumsCharts> getAlbumsChartsById() {
        return albumsChartsById;
    }

    public void setAlbumsChartsById(Collection<AlbumsCharts> albumsChartsById) {
        this.albumsChartsById = albumsChartsById;
    }
}
