public class Main {

    public static void main(String[] args) {
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
//create table album(
//    id integer not null,
//    name varchar(100) not null,
//    artist_id integer not null references artist(ID),
//    release_year integer,
//    primary key (id)
//    );
//
//create table chart(
//        id integer primary key not null,
//        name varchar(100) not null
//        )
//
//create table album_chart(
//        id integer primary key not null,
//        id_album integer not null references album(id),
//        id_chart integer not null references chart(id),
//        pos_in_chart integer not null
//        )

//drop sequence seqs;
//create sequence seqs minvalue 1 start with 1 increment by 1;
//
//drop sequence seqs2;
//create sequence seqs2 minvalue 1 start with 1 increment by 1;
