$conn = new mysqli ("localhost:3306", "root", "pass", "db_name");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

function getBookmarks(){
    global $conn;

    $stmt = $conn->prepare('SELECT * FROM bookmarks');

    if (false === $stmt ) {
        die('prepare() failed: ' . htmlspecialchars($conn->error));
    }

    $stmt->execute();
    $result = $stmt -> get_result();
    $rows = mysqli_fetch_all ($result, MYSQLI_ASSOC);

    return $rows;
}

function getBookmarkById($id){
    global $conn;

    $stmt = $conn->prepare('SELECT url FROM bookmarks where id = ?');
    $stmt->bind_param('s', $id);

    if (false === $stmt ) {
        die('prepare() failed: ' . htmlspecialchars($conn->error));
    }

    $stmt->execute();
    $result = $stmt -> get_result();
    $rows = mysqli_fetch_all ($result, MYSQLI_ASSOC);

    return $rows;
}