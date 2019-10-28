set serveroutput on;
create or replace type om as object (
    nume VARCHAR2 (20),
    prenume VARCHAR2 (20),
    varsta INT,
    sex VARCHAR2 (10),
    CONSTRUCTOR function om (p_nume varchar2, p_prenume varchar2, p_varsta int) RETURN SELF AS RESULT,
    NOT FINAL member procedure gateste,
    member procedure info,
    ORDER member function omsort (p_om2 om) return number
) NOT FINAL;
/

create or replace type body om as
    constructor function om (p_nume varchar2, p_prenume varchar2, p_varsta int) return self as result IS
    begin
        nume := p_nume;
        prenume := p_prenume;
        varsta := p_varsta;
        sex := 'm';
        return;
    end;

    member procedure gateste is
    begin
        DBMS_OUTPUT.PUT_LINE ('Am gatit.');
    end gateste;

    member procedure info is 
    begin
        DBMS_OUTPUT.PUT_LINE ('Nume: ' || nume || ', prenume: ' || prenume || ', varsta: ' || varsta || ', sex: ' || sex);
    end info;

    ORDER member function omsort (p_om2 om) return number is
    begin
        IF (self.varsta = p_om2.varsta) THEN return 0; END IF;
        IF (self.varsta < p_om2.varsta) THEN return -1; END IF;
        return 1;
    end omsort;
end;
/

create or replace TYPE femeie UNDER om(
    member procedure naste,
    member procedure naste (p_nume_copil VARCHAR2),
    OVERRIDING member procedure gateste
);
/

create or replace TYPE BODY femeie as
    OVERRIDING member procedure gateste AS
    BEGIN
        DBMS_OUTPUT.PUT_LINE ('Am gatit foarte bine!');
    END gateste;

    member procedure naste is
    begin
        DBMS_OUTPUT.PUT_LINE('Am nascut');
    end naste;

    member procedure naste (p_nume_copil VARCHAR2) IS
    begin
        DBMS_OUTPUT.PUT_LINE('Am nascut un copil cu numele ' || p_nume_copil);
    end naste;
END;
/

--drop table obj_om;
--/
--create table obj_om(
--    id INT PRIMARY KEY,
--    col1 om
--);
--/

create or replace function add_om(p_nume varchar2, p_prenume varchar2, p_varsta int) return int as
    v_nextId INT;
    v_cnt number;
begin
    select count(*) into v_cnt from obj_om;
    if (v_cnt = 0) then
        v_nextId := 0;
    else
        select max(id) into v_nextId from obj_om;
    end if;
    
    v_nextId := v_nextId + 1;
    insert into obj_om values (v_nextId, new om (p_nume, p_prenume, p_varsta));
    COMMIT;
    return v_nextId;
end add_om;
/

create or replace function get_om (p_id INT) return om as
    v_om om;
BEGIN
    select col1 into v_om from obj_om where id = p_id;
    return v_om;
END get_om;
/

DECLARE
    v_line obj_om%ROWTYPE;
    v_id INT;
BEGIN
--    insert into obj_om VALUES (1, om ('Nume1', 'Prenume1', 50));
--    insert into obj_om VALUES (2, om ('Nume2', 'Prenume2', 30));
--    insert into obj_om VALUES (3, om ('Nume3', 'Prenume3', 40));
--    insert into obj_om VALUES (4, om ('Nume4', 'Prenume4', 10));
--    insert into obj_om VALUES (5, om ('Nume5', 'Prenume5', 35));
--    insert into obj_om VALUES (6, om ('Nume6', 'Prenume6', 45));
--    v_id := add_om ('Nume', 'Prenume', 31);
--    dbms_output.put_line (v_id);
    for v_line in (select * from obj_om) loop
        v_line.col1.info();
    end loop;
END;

-----------JAVA-----------
/*
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
*/