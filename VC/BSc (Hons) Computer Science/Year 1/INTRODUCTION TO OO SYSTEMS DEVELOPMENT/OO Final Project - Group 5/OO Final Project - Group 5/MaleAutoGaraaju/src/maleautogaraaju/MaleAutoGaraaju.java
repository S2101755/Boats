/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package maleautogaraaju;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author shifaz 1700461
 */
public class MaleAutoGaraaju {
    
    private static Scanner scan = new Scanner(System.in);
    private static ArrayList<VehicleServices> servicesList = new ArrayList<>();
    private static ArrayList<JobSheet> jobSheets = new ArrayList<>();

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        Boolean exit = false;

        servicesList.add(new VehicleServices ("Change Tyres", 200.00));
        servicesList.add(new VehicleServices ("Battery Replacement", 100.00));
        servicesList.add(new VehicleServices ("Oil Change", 175.00));
        servicesList.add(new VehicleServices ("Full Service", 2500.00));

while (!exit) {
            System.out.println("==========================================================");
            System.out.println("********|||Welcome to Male' Auto Garage|||*******");
            System.out.println("==========================================================\n");
            System.out.println("Choose Menu");

            System.out.println("1) Admin Menu");
            System.out.println("2) Customer Menu");
            System.out.println("3) Exit\n");

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
                    exit = true;
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
            System.out.println("1) Add new item to service list");
            System.out.println("2) Remove item from service list");
            System.out.println("3) Show all services");
            System.out.println("4) Report of total Services");
            System.out.println("5) Back\n");
            System.out.println("==========================================================\n");

            int choice = scan.nextInt();
            switch (choice) {
                case 1:
                    System.out.print("Enter service name: ");
                    scan.nextLine();
                    String service = scan.nextLine();
                    System.out.print("Enter service price: ");
                    Double price = scan.nextDouble();
                    servicesList.add(new VehicleServices(service, price));
                    System.out.println("\nService added successfully!\n");
                    break;
                case 2:
                    System.out.print("Enter Service number: ");
                    scan.nextLine();
                    int VehicleServices = scan.nextInt();
                   
                    servicesList.remove(VehicleServices);
                    System.out.println("\nService added successfully!\n");
                    break;
                case 3:
                    printServiceList();
                    break;
                case 4:
                    double total = 0.00;
                    for (JobSheet job : jobSheets) {
                        System.out.println(job.job.service + " | Servicing Vehicle: " + job.vehicleNumber);
                        total += job.job.price;
                    }
                    System.out.println("Total : " + total);
                    break;
                case 5:
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
            System.out.println("1) Show Services");
            System.out.println("2) Select a Service");
            System.out.println("3) Confirm Service");
            System.out.println("4) Back\n");
            System.out.println("==========================================================\n");

            int choice = scan.nextInt();
            switch (choice) {
                case 1:
                    printServiceList();
                    break;
                case 2:
                    System.out.println("Enter Service No: ");
                    int serviceChoice = scan.nextInt();

                    System.out.println("Enter Vehicle Number: ");
                    scan.nextLine();
                    String vehiclenumber = scan.nextLine();

                    JobSheet currentJob = new JobSheet(servicesList.get(serviceChoice - 1), vehiclenumber);

                    jobSheets.add(currentJob);
                    System.out.println("==========================================================");
                    System.out.println("\t\t||Order Summary||");
                    System.out.println("==========================================================");
                    System.out.println("\tItem\t||\tPrice\t||\tAddress");
                    System.out.println("----------------------------------------------------------");
                    System.out.println(currentJob.job.service + "\t||\t" + currentJob.job.price + "\t||\t" + currentJob.vehicleNumber);
                    System.out.print("\n");

                    double total = 0.00;
                    for (JobSheet order : jobSheets) {
                        total += order.job.price;
                    }
                    System.out.println("Your current billed total is = " + total + "\n");

                    break;
                case 3:
                    customerExit = true;
                    System.out.println("==============================");
                    System.out.println("********|||Invoice|||*******");
                    System.out.println("==============================\n");
                    double total2 = 0.00;
                    for (JobSheet job : jobSheets) {
                        System.out.println(job.job.service + " | Price: " + job.job.price);
                        total2 += job.job.price;

                    }

                    
                    System.out.println("\nYour billed total is = " + total2 + "");
                    System.out.println("Please settle your bill.\n");
                    
                    System.out.println("=================================================");
                    System.out.println("********|||Visit us agian!|||*******");
                    System.out.println("==================================================\n");
                    break;
                case 4:
                    customerExit = true;
                    break;
                default:
                    System.out.println("Invalid Input, please choose an option from 1-3");
                    break;
            }
        }
    }

    public static void printServiceList() {
        for (VehicleServices item : servicesList) {
            System.out.println((servicesList.indexOf(item) + 1) + " - " + item.service + " - " + item.price);
        }
    }

}
