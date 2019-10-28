package controller;

import entity.Album;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import java.util.List;

public class AlbumController {
    private EntityManagerFactory emf;

    public AlbumController(EntityManagerFactory emf) {
        this.emf = emf;
    }

    public void create(Album album) {
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        em.persist(album);
        em.getTransaction().commit();
        em.close();
    }

    public Album findByName(String albumName) {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Artist t where t.name=:name");
        List<Album> albums = query.setParameter("name", albumName).getResultList();
        em.close();
        return albums.isEmpty() ? null : albums.get(0);
    }
}