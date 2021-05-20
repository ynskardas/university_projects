import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
// import SystemCatalogue;


public class StoreManager {
    public static void main(String[] args) throws IOException{
        String INPUT_FILE = args[0];
    //    System.out.println(INPUT_FILE);
        String OUTPUT_FILE = args[1];
    //    System.out.println(OUTPUT_FILE);


        SystemCatalogue syscat=new SystemCatalogue(INPUT_FILE, OUTPUT_FILE);
    }
}