import oracle.jdbc.OracleCallableStatement;
import oracle.jdbc.OracleTypes;

import java.math.BigDecimal;
import java.sql.*;
import java.util.concurrent.ThreadLocalRandom;

class Main {
    public static void main(String[] args) {
        Connection con = null;
        OracleCallableStatement returnStatement;
        Integer idForAddedObject;

        try {
            con = connectToDatabase(con);
            idForAddedObject = addNewObject(con, new Om());
            returnStatement = (OracleCallableStatement) con.prepareCall("BEGIN ? := get_om(?); END;");
            returnStatement.setInt(2, idForAddedObject);
            returnStatement.registerOutParameter(1, OracleTypes.JAVA_STRUCT, "OM");
            returnStatement.execute();
            oracle.sql.STRUCT deserializedOm = (oracle.sql.STRUCT) returnStatement.getObject(1);
            Object[] atributtes = deserializedOm.getAttributes();

            System.out.println("Nume: " + (String) atributtes[0] + ", Prenume: " + (String) atributtes[1] + ", Varsta: " + (BigDecimal)atributtes[2]);
        }

        // Handle any errors that may have occurred.
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static Integer addNewObject(Connection con, Om om) throws SQLException {
        CallableStatement stmt;
        Integer newObjectId;
        String SQL;

        stmt = con.prepareCall("BEGIN ? := add_om(?, ?, ?); END;");
        stmt.registerOutParameter(1, Types.INTEGER);
        stmt.setString(2, om.getNume());
        stmt.setString(3, om.getPrenume());
        stmt.setString(4, Integer.toString(om.getVarsta()));
        stmt.execute();
        newObjectId = stmt.getInt(1);

        if (stmt != null) try {
            stmt.close();
        } catch (Exception e) {
        }
        if (con != null) try {
            con.commit();
            con.close();
        } catch (Exception e) {
        }
        return newObjectId;
    }

    private static Connection connectToDatabase(Connection con) throws SQLException {
        String connectionUrl = "jdbc:oracle:thin:@localhost:1521:XE";
        con = DriverManager.getConnection(connectionUrl, "student", "STUDENT");
        return con;
    }
}

class Om {
    String nume;
    String prenume;
    int varsta;

    Om() {
        nume = "NumeJava";
        prenume = "PrenumeJava";
        varsta = ThreadLocalRandom.current().nextInt(10, 100);
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }
}