package t4.q2;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author == Shauzab ==
 * 
 */
public class T4Q2 {

    public static void main(String[] args) {
        
        try {
            File myFile = new File("stringFile.txt");
            Scanner fileRd = new Scanner(myFile);

            while (fileRd.hasNextLine()) 
            {
                String str = fileRd.nextLine();
                System.out.println("\n"+str);
                
                System.out.println("Length of the string is: " + str.length());
            }
            
        } catch (FileNotFoundException e)
        {
            System.out.println("ERROR!");
            e.printStackTrace();
        }
        
    }
    
}
