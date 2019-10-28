package app;

import controller.ArtistController;
import entity.Albums;
import entity.Artists;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;
import java.util.List;
import java.util.Scanner;

public class AlbumManager {
    static final EntityManagerFactory emf = Persistence.createEntityManagerFactory("MusicAlbumsPU");

    public void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Input command:");
            String command = scanner.nextLine();
            System.out.println("Received command: " + command);
            if (command.equals("exit")) break;
            String[] params = command.trim().split("\\s+");
            switch (params[0]) {
                case "create-artist":
                    createArtist(params[1]); //the artist name
                    break;
                case "create-album":
                    createAlbum(params[1], params[2]); //the album name and the artist name
                    break;
                case "list-albums":
                    listAlbums(params[1]); //the artist name
                    break;
            }
        }
    }

    private void createArtist(String artistName) {
        Artists artist = new Artists(artistName);
        ArtistController artistController = new ArtistController(emf);
        artistController.create(artist);
    }

    private void createAlbum(String albumName, String artistName) {
        Integer artistId = getIdFromArtist (artistName);
        Albums album = new Albums (albumName, getArtistFromDatabase(artistName));
		//Implement this method
    }

    private Artists getArtistFromDatabase(String artistName) {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Artists t where t.name=:artistName");
        List <Artists> artists = query.setParameter("artistName", artistName).getResultList();
        return artists.get(0);
    }

    private Integer getIdFromArtist(String artistName) {
        ArtistController artistController = new ArtistController(emf);
        Artists artist = artistController.findByName(artistName);
        return (int)artist.getId();
    }

    private void listAlbums(String artistName) {
		//Implement this method
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Albums t where t.artist_id=:artistId");
        List<Albums> albums = query.setParameter("artistId", getIdFromArtist(artistName)).getResultList();

        for (Albums album : albums){
            System.out.println(album.toString());
        }
    }
}