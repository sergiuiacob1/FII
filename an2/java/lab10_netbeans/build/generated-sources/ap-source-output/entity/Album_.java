package entity;

import java.math.BigDecimal;
import java.math.BigInteger;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Album.class)
public abstract class Album_ {

	public static volatile CollectionAttribute<Album, AlbumChart> albumChartCollection;
	public static volatile SingularAttribute<Album, String> name;
	public static volatile SingularAttribute<Album, Artist> artistId;
	public static volatile SingularAttribute<Album, BigDecimal> id;
	public static volatile SingularAttribute<Album, BigInteger> releaseYear;

}

