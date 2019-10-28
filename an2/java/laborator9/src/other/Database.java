package other;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Database {
        private static final String URL = "jdbc:derby://localhost:1527/MusicAlbums";
        private static final String USER = "dba";
        private static final String PASSWORD = "sql";
        private static Connection connection = null;

        private Database() {
        }

        public static Connection getConnection() throws SQLException, ClassNotFoundException {
            if (connection == null) {
                createConnection();
            }
            return connection;
        }

        public static void createConnection() throws ClassNotFoundException, SQLException {
            Class.forName("oracle.jdbc.driver.OracleDriver");
            connection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:xe","DBA1","SQL1");
            connection.setAutoCommit(false);
        }

        public static void commit() throws SQLException {
            connection.commit();
        }

        public static void closeConnection() throws SQLException {
            connection.close();
        }

        public static void rollback() throws SQLException {
            connection.rollback();
        }
    }
