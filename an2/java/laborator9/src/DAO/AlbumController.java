package DAO;

import other.Database;

import java.sql.*;

public class AlbumController {
    public void create(int artistId, String nume,  int year) throws SQLException, ClassNotFoundException {
        Connection con = Database.getConnection();
        ResultSet idValid = con.createStatement().executeQuery("select seqs2.nextval from dual");
        idValid.next();
        int id = idValid.getInt(1);
        try (PreparedStatement pstmt = con.prepareStatement("insert into albums (id, name, artist_id, release_year) values (?, ?, ?, ?)")) {
            pstmt.setInt(1, id);
            pstmt.setString(2, nume);
            pstmt.setInt(3, artistId);
            pstmt.setInt(4, year);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public Integer findByName(String name) throws SQLException, ClassNotFoundException {
        Connection con = Database.getConnection();
        PreparedStatement pstmt = con.prepareStatement("select id from albums where name = (?)");
        pstmt.setString(1, name);
        ResultSet id = pstmt.executeQuery();
        //
        if(id.next())
            return id.getInt(1);
        return null;
    }

    public void list(Integer id) throws SQLException, ClassNotFoundException {
        Connection con = Database.getConnection();
        PreparedStatement pstmt = con.prepareStatement("select name from albums where artist_id = (?)");
        pstmt.setInt(1, id);
        ResultSet rs = pstmt.executeQuery();
        System.out.println("Albums for artist with id = " + id);
        while(rs.next()){
            System.out.println(rs.getString(1));
        }
    }
}