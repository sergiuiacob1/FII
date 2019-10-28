package entity;

import java.math.BigDecimal;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(AlbumChart.class)
public abstract class AlbumChart_ {

	public static volatile SingularAttribute<AlbumChart, BigDecimal> id;
	public static volatile SingularAttribute<AlbumChart, Album> idAlbum;
	public static volatile SingularAttribute<AlbumChart, Chart> idChar;

}

