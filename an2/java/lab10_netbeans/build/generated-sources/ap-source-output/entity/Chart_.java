package entity;

import java.math.BigDecimal;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value = "org.hibernate.jpamodelgen.JPAMetaModelEntityProcessor")
@StaticMetamodel(Chart.class)
public abstract class Chart_ {

	public static volatile CollectionAttribute<Chart, AlbumChart> albumChartCollection;
	public static volatile SingularAttribute<Chart, String> name;
	public static volatile SingularAttribute<Chart, BigDecimal> id;

}

