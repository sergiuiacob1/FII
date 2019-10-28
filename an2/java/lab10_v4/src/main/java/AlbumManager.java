import controller.AlbumController;
import controller.ArtistController;
import entity.Album;
import entity.Artist;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;
import java.util.Arrays;
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

        emf.close();
    }

    private void createArtist(String artistName) {
        Artist artist = new Artist(artistName);
        ArtistController artistController = new ArtistController(emf);
        artistController.create(artist);
    }

    private void createAlbum(String albumName, String artistName) {
        AlbumController albumController = new AlbumController(emf);
        ArtistController artistController = new ArtistController(emf);
        albumController.create(new Album(albumName, artistController.findByName(artistName)));
    }

    private Artist getArtistFromDatabase(String artistName) {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("select t from Artist t where t.name=:artistName");
        List<Artist> artists = query.setParameter("artistName", artistName).getResultList();
        return artists.get(0);
    }

    private Integer getIdFromArtist(String artistName) {
        ArtistController artistController = new ArtistController(emf);
        Artist artist = artistController.findByName(artistName);
        return (int) artist.getId();
    }

    private void listAlbums(String artistName) {
        ArtistController artistController = new ArtistController(emf);
        Artist artist = artistController.findByName(artistName);

//        System.out.println(Arrays.toString(artist.getAlbums().toArray()));

    }
}