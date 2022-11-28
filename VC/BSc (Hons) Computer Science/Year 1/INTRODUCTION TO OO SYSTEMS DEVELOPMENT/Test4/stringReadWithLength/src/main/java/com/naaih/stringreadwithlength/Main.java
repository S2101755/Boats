package com.naaih.stringreadwithlength;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {
        try {
            File myFile = new File("stringFile.txt");
            Scanner fileRd = new Scanner(myFile);

            while (fileRd.hasNextLine()) {
                String str = fileRd.nextLine();
                System.out.println("\n"+str);
                
                System.out.println("Length of the string is: " + str.length());
            }
            
        } catch (FileNotFoundException e) {
            System.out.println("ERROR!");
            e.printStackTrace();
        }
    }

}
