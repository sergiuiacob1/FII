package controller;

import entity.Artist;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import java.util.List;

public class ArtistController {
    private EntityManagerFactory emf;

    public ArtistController(EntityManagerFactory emf) {
        this.emf = emf;
    }

    public void create(Artist artist) {
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();
        em.persist(artist);
        em.getTransaction().commit();
        em.close();
    }

    public Artist findByName(String artistName) {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Artist t where t.name=:name");
        List<Artist> artists = query.setParameter("name", artistName).getResultList();
        em.close();
        return artists.isEmpty() ? null : artists.get(0);
    }
}