package DAO;

import other.Database;

import java.sql.*;

public class ArtistController {
    public void create(String name, String country) throws SQLException, ClassNotFoundException {
        Connection con = Database.getConnection();
        ResultSet idValid = con.createStatement().executeQuery("select seqs.nextval from dual");
        idValid.next();
        int id = idValid.getInt(1);
        //
        try (PreparedStatement pstmt = con.prepareStatement("insert into artists (id, name, country) values (?, ?, ?)")) {
            pstmt.setInt(1, id);
            pstmt.setString(2, name);
            pstmt.setString(3, country);
            pstmt.executeUpdate();
        }
    }
    public Integer findByName(String name) throws SQLException, ClassNotFoundException {
        Connection con = Database.getConnection();
        PreparedStatement pstmt = con.prepareStatement("select id from artists where name = (?)");
        pstmt.setString(1, name);
        ResultSet id = pstmt.executeQuery();
        //
        if(id.next())
            return id.getInt(1);
        return null;
    }
}