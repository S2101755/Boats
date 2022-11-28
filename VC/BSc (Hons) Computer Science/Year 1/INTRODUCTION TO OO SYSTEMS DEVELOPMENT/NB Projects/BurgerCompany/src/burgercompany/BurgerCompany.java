/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package burgercompany;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Asus
 */
public class BurgerCompany {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
                
        DrinksMenu drink1 = new DrinksMenu(01,"Chocolate Milkshake",25.90);
        DrinksMenu drink2 = new DrinksMenu(02,"Strawberry Milkshake",25.90);
        DrinksMenu drink3 = new DrinksMenu(03,"Vanilla Milkshake",25.90);
        DrinksMenu drink4 = new DrinksMenu(04,"Shake Shake Milkshake",30.30);
        
        drink1.display();
        drink2.display();
        drink3.display();
        drink4.display();
        
   
        
    }
    
}
