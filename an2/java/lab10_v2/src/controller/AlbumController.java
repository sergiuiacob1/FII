package controller;

import entity.Albums;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import java.util.List;

public class AlbumController {
    private EntityManagerFactory emf;

    public AlbumController(EntityManagerFactory emf) {
        this.emf = emf;
    }

    public void create(Albums album) {
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        em.persist(album);
        em.getTransaction().commit();
        em.close();
    }

    public Albums findByName(String albumName) {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Artists t where t.name=:name");
        List<Albums> albums = query.setParameter("name", albumName).getResultList();
        em.close();
        return albums.isEmpty() ? null : albums.get(0);
    }
}