set serveroutput on;
--
--<form action="index.php" method="post">
--<table width="50%">
--    <tr>
--        <td>id stud</td>
--        <td><input type="text" name="id"></td>
--    </tr>
--</table>
--    <input type="submit" value="OK" name="send">
--</form>
--
--<?php
--    $username = 'student';
--    $password = 'STUDENT';
--    $connection_string = 'localhost/xe';
--
--    //Connect to an Oracle database
--    $connection = oci_connect($username, $password, $connection_string);
--
--    if (!$connection)
--        echo 'Connection failed';
--
--    if (isset($_POST['id'])){
--        $id = $_POST['id'];
--        $stid = oci_parse($connection, "select nume, prenume from studenti where id = :myId");
--        oci_bind_by_name ($stid, ":myId", $id);
--        oci_execute($stid);
--        oci_close($connection);
--
--        echo "<table border='1'>\n";
--        while ($row = oci_fetch_array($stid, OCI_ASSOC+OCI_RETURN_NULLS)) {
--            echo "<tr>\n";
--            foreach ($row as $item) {
--                echo "    <td>" . ($item !== null ? htmlentities($item, ENT_QUOTES) : "&nbsp;") . "</td>\n";
--            }
--            echo "</tr>\n";
--        }
--        echo "</table>\n";
--    }
--?>