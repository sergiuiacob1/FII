import sqlite3
from sqlite3 import Error
import zipfile
import os

db_name = 'chinook.db'


def get_database_zip_path(current_path):
    current_path = os.path.abspath(current_path)
    for root, dirs, files in os.walk(current_path):
        for f in files:
            if f.endswith('.zip'):
                return os.path.abspath(os.path.join(root, f))

    return None


def create_connection(db_file):
    """ create a database connection to the SQLite database
        specified by the db_file
    :param db_file: database file
    :return: Connection object or None
    """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Error as e:
        print(e)

    return conn


def get_data_from_db(db_path, low, high):
    conn = create_connection(db_path)
    data = select_tracks(conn, low, high)
    return sorted(data)


def select_tracks(conn, low, high):
    cur = conn.cursor()
    statement = "SELECT a.Title, t.Name, g.Name FROM tracks t join albums a on t.AlbumId = a.AlbumId join genres g on t.GenreId = g.GenreId WHERE t.Milliseconds>=? AND t.Milliseconds<=?"
    cur.execute(statement, (low, high,))

    rows = cur.fetchall()
    return rows


def get_db_path_in_zip(zip_path):
    z = zipfile.ZipFile(zip_path)
    for i in z.infolist():
        if i.filename.endswith(db_name):
            z.extract(i.filename, '.')
            return os.path.join('.', db_name)
    return None


def problema1(path, low, high):
    zip_path = get_database_zip_path(path)
    db_path = get_db_path_in_zip(zip_path)

    data = get_data_from_db(db_path, low, high)
    return data


def main():
    print(problema1('..', 330000, 330200))


if __name__ == '__main__':
    main()
