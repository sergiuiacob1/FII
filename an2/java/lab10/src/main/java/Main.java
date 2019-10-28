import app.AlbumManager;

public class Main {

    public static void main(String []args){
        AlbumManager albumManager = new AlbumManager();
        albumManager.run();
    }
}

//create table artists(
//    id integer not null,
//    name varchar(100) not null,
//    country varchar(100),
//    primary key (id)
//    );
//
//create table albums(
//    id integer not null,
//    name varchar(100) not null,
//    artist_id integer not null references artists(ID),
//    release_year integer,
//    primary key (id)
//    );
//
//create table charts(
//        id integer primary key not null,
//        name varchar(100) not null
//        )
//
//create table albums_charts(
//        id integer primary key not null,
//        id_album integer not null references albums(id),
//        id_char integer not null references charts(id)
//        )