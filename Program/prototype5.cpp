
public interface Prototype {
	public abstract Object clone ( );
}

 

public class ConcretePrototype implements Prototype {
	public Object clone() {
		return super.clone();
	}
}

public class Client {

	public static void main( String arg[] ) 
	{
		ConcretePrototype obj1= new ConcretePrototype ();
		ConcretePrototype obj2 = ConcretePrototype)obj1.clone();
	}

}