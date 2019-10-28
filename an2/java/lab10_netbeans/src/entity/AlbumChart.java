/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package entity;

import java.io.Serializable;
import java.math.BigDecimal;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author sergiu
 */
@Entity
@Table(name = "ALBUM_CHART")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "AlbumChart.findAll", query = "SELECT a FROM AlbumChart a")
    , @NamedQuery(name = "AlbumChart.findById", query = "SELECT a FROM AlbumChart a WHERE a.id = :id")})
public class AlbumChart implements Serializable {

    private static final long serialVersionUID = 1L;
    // @Max(value=?)  @Min(value=?)//if you know range of your decimal fields consider using these annotations to enforce field validation
    @Id
    @Basic(optional = false)
    @Column(name = "ID")
    private BigDecimal id;
    @JoinColumn(name = "ID_ALBUM", referencedColumnName = "ID")
    @ManyToOne(optional = false)
    private Album idAlbum;
    @JoinColumn(name = "ID_CHAR", referencedColumnName = "ID")
    @ManyToOne(optional = false)
    private Chart idChar;

    public AlbumChart() {
    }

    public AlbumChart(BigDecimal id) {
        this.id = id;
    }

    public BigDecimal getId() {
        return id;
    }

    public void setId(BigDecimal id) {
        this.id = id;
    }

    public Album getIdAlbum() {
        return idAlbum;
    }

    public void setIdAlbum(Album idAlbum) {
        this.idAlbum = idAlbum;
    }

    public Chart getIdChar() {
        return idChar;
    }

    public void setIdChar(Chart idChar) {
        this.idChar = idChar;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof AlbumChart)) {
            return false;
        }
        AlbumChart other = (AlbumChart) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "lab10_netbeans.AlbumChart[ id=" + id + " ]";
    }
    
}
