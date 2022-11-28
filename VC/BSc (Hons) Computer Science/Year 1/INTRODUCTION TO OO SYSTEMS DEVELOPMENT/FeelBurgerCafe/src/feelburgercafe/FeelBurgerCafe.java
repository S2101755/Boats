/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package feelburgercafe;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author shifaz
 */
public class FeelBurgerCafe {

    private static final Scanner scan = new Scanner(System.in);
    private static final ArrayList<FoodItem> masterList = new ArrayList<>();
    private static final ArrayList<FoodOrder> foodOrders = new ArrayList<>();
    private static final ArrayList<FoodOrder> cOrder = new ArrayList<>();

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Boolean main = false;

        masterList.add(new FoodItem("Fried Chicken Burger", 60.00));
        masterList.add(new FoodItem("Beef Burger", 70.00));
        masterList.add(new FoodItem("Signature Burger", 90.00));
        masterList.add(new FoodItem("Kids Burger", 55.00));
        masterList.add(new FoodItem("Double Meat Burger", 85.00));
        
        while (!main) {
            System.out.println("==========================================================");
            System.out.println("********|||Welcome to Feel Burger Cafe & Bistro|||*******");
            System.out.println("==========================================================\n");
            System.out.println("Choose Menu");
            
            System.out.println("1) Admin Menu");
            System.out.println("2) Customer Menu");
            System.out.println("3) Exit\n");
            System.out.println("Press 3 when you're done");
            System.out.println("==========================================================\n");
            int choice = scan.nextInt();
            switch (choice) {
                case 1:
                    adminMenu();
                    break;
                case 2:
                    customerMenu();
                    break;
                case 3:
                    main = true;
                    System.out.println("==========================================================");
                    System.out.println("Please settle your bill at the counter\n");
                    double total = 0.00;
                    for (FoodOrder order : foodOrders) {
                        System.out.println(order.item.name + " | Price: " + order.item.price);
                        total += order.item.price;
                    }
                    System.out.println("==========================================================");
                    System.out.println("\t********|||Hope to seeyou soon|||*******");
                    System.out.println("==========================================================\n");
                    System.out.println("Please settle your bill at the counter");
                    System.out.println("Your billed total is = "+total+"\n");
                    System.out.println("Thank you.\nHave a nice day!");
                    break;
                default:
                    System.out.println("Invalid Input, please choose an option from 1-3");
                    break;
            }
        }
    }

    public static void adminMenu() {
        Boolean adminExit = false;
        while (!adminExit) {
            System.out.println("==========================================================");
            System.out.println("     \t\t***||Admin Menu||***");
            System.out.println("==========================================================\n");
            System.out.println("1) Add new food item to master list");
            System.out.println("2) Show all food items");
            System.out.println("3) Report of total food orders");
            System.out.println("4) Back\n");
            System.out.println("==========================================================\n");

            int choice = scan.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Enter item name: ");
                    scan.nextLine();
                    String name = scan.nextLine();
                    System.out.print("Enter item price: ");
                    Double price = scan.nextDouble();
                    masterList.add(new FoodItem(name, price));
                    System.out.println("\nItem added successfully!\n");
                    break;
                case 2:
                    printMasterList();
                    break;
                case 3:
                    double total = 0.00;
                    for (FoodOrder order : foodOrders) {
                        System.out.println(order.item.name + " | Deliver to: " + order.deliveryAddress);
                        total += order.item.price;
                    }
                    System.out.println("Total : " + total);
                    break;
                case 4:
                    adminExit = true;
                    break;
                default:
                    System.out.println("Invalid Input, please choose an option from 1-4");
                    break;
            }
        }
    }

    public static void customerMenu() {

        Boolean customerExit = false;
        while (!customerExit) {
            System.out.println("==========================================================");
            System.out.println("\t\t***||Customer Menu||***");
            System.out.println("==========================================================\n");
            System.out.println("1) Show Items");
            System.out.println("2) Place Order");
            System.out.println("3) Back\n");
            System.out.println("==========================================================\n");

            int choice = scan.nextInt();
            switch (choice) {
                case 1:
                    printMasterList();
                    break;
                case 2:
                    System.out.println("Enter Item No: ");
                    int itemChoice = scan.nextInt();

                    System.out.println("Enter delivery address: ");
                    scan.nextLine();
                    String address = scan.nextLine();

                    FoodOrder currentOrder = new FoodOrder(masterList.get(itemChoice), address);

                    foodOrders.add(currentOrder);
                    System.out.println("==========================================================");
                    System.out.println("\t\t||Order Summary||");
                    System.out.println("==========================================================");
                    System.out.println("\tItem\t||\tPrice\t||\tAddress");
                    System.out.println("----------------------------------------------------------");
                    System.out.println(currentOrder.item.name + "\t||\t" + currentOrder.item.price + "\t||\t" + currentOrder.deliveryAddress);
                    System.out.print("\n");
                    System.out.println("\nOrder details: \n");
                    double total = 0.00;
                    for (FoodOrder order : foodOrders) {
                        System.out.println(order.item.name + " | Price: " + order.item.price);
                        total += order.item.price;
                    }
                    System.out.println("Your billed total is = "+total+"\n");
                    System.out.println("** Order placed successfully! **\n\n");//when items ready to dispatch
                    System.out.println("Do you want to continue with your order?");
                    
                    break;
                case 3:
                    customerExit = true;
                    break;
                default:
                    System.out.println("Invalid Input, please choose an option from 1-3");
                    break;
            }
        }
    }

    public static void printMasterList() {
        for (FoodItem item : masterList) {
            System.out.println((masterList.indexOf(item) + 1) + " - " + item.name + " - " + item.price);
        }
    }

}