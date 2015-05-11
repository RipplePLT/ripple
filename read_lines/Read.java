import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class Read {

	public static void main(String [] args){
		
		try {
                    while(true){
			BufferedReader fileReader = new BufferedReader(new FileReader("hello.txt"));
			for(String s = fileReader.readLine(); s != null; s = fileReader.readLine()){
				System.out.println(s);
                                Thread.sleep(1000);
                        }
			fileReader.close();
                    }
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
