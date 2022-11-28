
package avasservices;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author ShauXab
 */
public class AvasServices {

    /**
     * @param args the command line arguments
     */
    private static final ArrayList<CycleService> cyList = new ArrayList<>();
    private static final ArrayList<Customer> cusList = new ArrayList<>();
    private static final ArrayList<CurrSer> currSer = new ArrayList<>();
    private static final Scanner scan = new Scanner(System.in);
    
    
    public static void main(String[] args) {
 
    cyList.add(new CycleService("Honda","\tZoomer x",107));
    cyList.add(new CycleService("Honda","\tWave 125",128));
    cyList.add(new CycleService("Honda","\tWave 150",137));
    cyList.add(new CycleService("Honda","\tScoopy i",114));
    cyList.add(new CycleService("Honda","\tAirBlade 125",135));
    cyList.add(new CycleService("Honda","\tAirBlade 150",139));
    cyList.add(new CycleService("Honda","\tPCX 150\t",136));
    cyList.add(new CycleService("Suzuki","\tGN 125\t",148));
    cyList.add(new CycleService ("Yamaha","\tMio Fino",133));
    cyList.add(new CycleService ("Yamaha","\tSniper MX",140));
    
    Boolean main = false;
    
    while (!main){
            System.out.println("==================================================================");
            System.out.println("<<<<<<<<<||||||\t WELCOME TO FEEL MOTOR SERVICES\t||||||>>>>>>>>>");
            System.out.println("==================================================================\n");
            System.out.println("Please fill in your details.\n");
            System.out.println("Press enter to continue.");
            
            scan.nextLine();
            System.out.println("Full Name: \n");
            String custName = scan.nextLine();
            
 
            System.out.println("Current Address: \n");
            String custAddress = scan.nextLine();
            
            
            System.out.println("Mobile Number: \n");
            int custMNum = scan.nextInt();
            scan.nextLine();

            System.out.println("Vehicle Registration Number (Motorcycle board number): \n");
            String boardNum = scan.nextLine();
            
            cusList.add(new Customer(custName, custMNum, custAddress, boardNum));
            System.out.println("Thank you!"); System.out.println("Welcome to Feel Motor Services");
            System.out.println("==================================================================\n");
            
            System.out.println("Please choose an option from below...\n");
            
            System.out.println("1 :\t \tMotorcycle wash and maintenance \t\t:");
            System.out.println("2 :\t \tEngine related services \t\t:");
            System.out.println("3 :\t \tOther services \t\t\t\t:");
            System.out.println("4 :\t \tExit \t\t\t\t\t:\n");
            System.out.println("==================================================================\n");
//    Case4   int total = 0;
//            for (CurrSer cusss : currSer) {
//                        System.out.println("Your billed total is: "+total);
//                        total += cusss.cycleName.Price;
//            }

            int choice = scan.nextInt();
            switch (choice){
                case 1:
                    
                    Service();
                    break;
                case 4:
                    main = true;
                    
                    System.out.println("\t\t======   Customer Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Customer Name \t|| Contact Number \t|| Motorcycle Registration");
                    System.out.println("==================================================================");
                    for (Customer cusss : cusList) {
                        System.out.println(cusss.custName + "\t\t||\t"+ cusss.custMNum + "\t\t||\t"+cusss.boardNum +"\n");}
                    
                    System.out.println("\t\t======   Service Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Motorcycle\t\t||\t\tPrice");
                    System.out.println("==================================================================");
                    int total = 0;
                    for (CurrSer ser : currSer) {
                        System.out.println(ser.cycleName.cycleBrand + ser.cycleName.cycleName +"\t\t\t"+ ser.cycleName.Price);
                        total += ser.cycleName.Price;
                    }
                    System.out.println("==================================================================");
                    System.out.println("Grand total: \t\t\t\t"+total*4+"\n");
                    System.out.println("\nPlease settle your bill before exit.\n");
                    System.out.println("\t\t\t***Thank you!***\t\t\n");
                    break;
            }
            
                
                    
                }
        
        }
    
    public static void Service() {
            Boolean servExit = false;
        while (!servExit) {
            System.out.println("==================================================================");
            System.out.println("\t\t***||MOTORCYCLE WASH AND MAINTENANCE||***");
            System.out.println("==================================================================\n");
            System.out.println("1 :\t \tWash without service \t\t\t:");
            System.out.println("2 :\t \tWash and full service \t\t\t:");
            System.out.println("3 :\t \tGo back \t\t\t\t:\n");
            System.out.println("==================================================================\n");

            int choice = scan.nextInt();
            switch (choice) {
                case 1 -> {
                    System.out.println("\tBRAND\t|| \tNAME\t \t||\tSERVICE PRICE");
                    int i = 0;
                    System.out.println("==================================================================\n");
                    for (CycleService cyy : cyList) {
                        System.out.println(i++ +"\t" + cyy.cycleBrand + "\t||"+ cyy.cycleName + "\t"+ "||\t"+cyy.Price*4 + "\t\n");}
                        
                    System.out.println("Select your motorcycle from the list");
                    int moto = scan.nextInt();
                    System.out.println("You have selected option " +moto+ "\nPress any key to continue");
                    String cont = scan.next();
                    
                    
                    CurrSer motonew = new CurrSer(cyList.get(moto), cont);
                    currSer.add(motonew);
                    System.out.println("\t\t======   Customer Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Customer Name \t|| Contact Number \t|| Motorcycle Registration");
                    System.out.println("==================================================================");
                    for (Customer cusss : cusList) {
                        System.out.println(cusss.custName + "\t\t||\t"+ cusss.custMNum + "\t\t||\t"+cusss.boardNum +"\n");}
                    
                    System.out.println("\t\t======   Service Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Motorcycle\t\t||\t\tPrice");
                    System.out.println("==================================================================");
                    int total = 0;
                    for (CurrSer ser : currSer) {
                        System.out.println(ser.cycleName.cycleBrand + ser.cycleName.cycleName +"\t\t\t"+ ser.cycleName.Price*4);
                        total += ser.cycleName.Price;
                    }
                    System.out.println("\n\n\n");
                    System.out.println("==================================================================");
                    System.out.println("Grand total: \t\t\t\t"+total*4);
                    System.out.println("==================================================================\n");
                    System.out.println("Please settle your bill before exit.\n");
                    System.out.println("==================================================================\n");
                    System.out.println("\t\t\t***Thank you!***\t\t\n");
                    break;
                    }
                case 2 -> {
                    System.out.println("\tBRAND\t|| \tNAME\t \t||\tSERVICE PRICE");
                    int i = 0;
                    System.out.println("==================================================================\n");
                    for (CycleService cyy : cyList) {
                        System.out.println(i++ +"\t" + cyy.cycleBrand + "\t||"+ cyy.cycleName + "\t"+ "||\t"+cyy.Price*11 + "\t\n");}
                        
                    System.out.println("Select your motorcycle from the list");
                    int moto = scan.nextInt();
                    System.out.println("You have selected option " +moto+ "\nPress any key to continue");
                    String cont = scan.next();
                    
                    
                    CurrSer motonew = new CurrSer(cyList.get(moto), cont);
                    currSer.add(motonew);
                    System.out.println("\t\t======   Customer Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Customer Name \t|| Contact Number \t|| Motorcycle Registration");
                    System.out.println("==================================================================");
                    for (Customer cusss : cusList) {
                        System.out.println(cusss.custName + "\t\t||\t"+ cusss.custMNum + "\t\t||\t"+cusss.boardNum +"\n");}
                    
                    System.out.println("\t\t======   Service Details   ======");
                    System.out.println("==================================================================");
                    System.out.println("Motorcycle\t\t||\t\tPrice");
                    System.out.println("==================================================================");
                    int total = 0;
                    for (CurrSer ser : currSer) {
                        System.out.println(ser.cycleName.cycleBrand + ser.cycleName.cycleName +"\t\t\t"+ ser.cycleName.Price*11);
                        total += ser.cycleName.Price;
                    }
                    System.out.println("\n\n\n");
                    System.out.println("==================================================================");
                    System.out.println("Grand total: \t\t\t\t"+total*11);
                    System.out.println("==================================================================\n");
                    System.out.println("Please settle your bill before exit.\n");
                    System.out.println("==================================================================\n");
                    System.out.println("\t\t\t***Thank you!***\t\t\n");
                    break;
                    }
                case 3 -> {
                    servExit = true;
                    break;
                }
                    
            }
        }
    }

    public static void eService(){
        
    }
    public static void CycleList() {
        for (CycleService cycle : cyList) {
            System.out.println((cyList.indexOf(cycle) + 1) + " - " + cycle.cycleName + " - " + cycle.cycleBrand);
            //CycleList();
        }
    }
    
    public static void CustList() {
        for (Customer cust : cusList) {
            System.out.println((cusList.indexOf(cust) + 1) + " = " + cust.custName);
            //CustList();
        }
    }
    
}