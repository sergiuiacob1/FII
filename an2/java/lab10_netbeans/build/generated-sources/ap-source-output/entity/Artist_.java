package entity;

import java.math.BigDecimal;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Artist.class)
public abstract class Artist_ {

	public static volatile SingularAttribute<Artist, String> country;
	public static volatile SingularAttribute<Artist, String> name;
	public static volatile CollectionAttribute<Artist, Album> albumCollection;
	public static volatile SingularAttribute<Artist, BigDecimal> id;

}

