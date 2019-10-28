package entity;

import javax.persistence.*;
import java.util.Collection;
import java.util.Objects;

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
        return id == charts.id &&
                Objects.equals(name, charts.name);
    }

    @Override
    public int hashCode() {

        return Objects.hash(id, name);
    }

    @OneToMany(mappedBy = "chartsByIdChar")
    public Collection<AlbumsCharts> getAlbumsChartsById() {
        return albumsChartsById;
    }

    public void setAlbumsChartsById(Collection<AlbumsCharts> albumsChartsById) {
        this.albumsChartsById = albumsChartsById;
    }
}
