/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package burgercompany;

/**
 *
 * @author Asus
 */
public class DrinksMenu {
    int drinkID;
    String drinkName;
    double drinkPrice;
    
    
    DrinksMenu (int dID, String dName, double dPrice){
        this.drinkID = dID;
        this.drinkName = dName;
        this.drinkPrice = dPrice;
    }
    
    //Getters
    public int getdrinkID(){
        return this.drinkID;
    }
    
    public String getdrinkName(){
        return this.drinkName;
    }
    
      public double getdrinkPrice(){
        return this.drinkPrice;
    }
      
    //Setters  
    public void setdrinkID(int dID){
        this.drinkID = dID;
    }
      
    public void setdrinkName(String dName){
        this.drinkName = dName;
    }
    
    public void setdrinkPrice(double dPrice){
        this.drinkPrice = dPrice;
    }
    
    
    
    
    
    public void display(){
        System.out.println("Menu Item No. : "+this.drinkID);
        System.out.println("Menu Item Name : "+this.drinkName);
        System.out.println("Menu Item Price : "+this.drinkPrice+"\n");
    }
}


