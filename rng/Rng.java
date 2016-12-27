import java.util.Random;
public class Rng{
	public static void main(String[] args){
		Random rand = new Random();
		for(int x = 0; x < 2000; x++){
			System.out.print(rand.nextDouble()+", ");
		}
	}
}
