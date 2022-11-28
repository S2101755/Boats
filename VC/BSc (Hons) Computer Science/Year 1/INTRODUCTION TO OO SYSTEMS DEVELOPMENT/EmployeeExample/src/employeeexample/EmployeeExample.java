/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package employeeexample;
import java.util.Scanner;

/**
 *
 * @author CompLab3
 */
public class EmployeeExample {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        //create a object
        FullTimeEmployee ft_emp = new FullTimeEmployee(1001, "Ali", "IT",10500.30);
        ft_emp.display();
        //lets create an another object from part time
        PartTimeEmployee pt_emp1 = new PartTimeEmployee(1002, "Aisha", "Front Desk", 30);
        System.out.println("Id = "+pt_emp1.getId());
         System.out.println("Name = "+pt_emp1.getName());
          System.out.println("Department = "+pt_emp1.getDepartment());
           System.out.println("Hours worked = "+pt_emp1.getTimeSheet());
           //lets create object from default constructor and ask user to enter values
        PartTimeEmployee pt_emp2 = new PartTimeEmployee();
        //now calling getter will show empty values
          System.out.println("Id = "+pt_emp2.getId());
          //lets ask the user to enter values
          Scanner scan = new Scanner(System.in);
          System.out.println("Enter staff id");
          int staff_id = scan.nextInt();
          //pass it to class object variable
          pt_emp2.setId(staff_id);
          System.out.println("Enter staff Name");
          String staff_name = scan.next();
          //pass it to class object variable
          pt_emp2.setName(staff_name);
          System.out.println("Enter staff Department");
          String staff_dept = scan.next();
          //pass it to class object variable
          pt_emp2.setDepartment(staff_dept);
          System.out.println("Enter staff worked hours");
          int staff_hours = scan.nextInt();
          //pass it to class object variable
          pt_emp2.setTimeSheet(staff_hours);
          //lets display
          System.out.println("displaying after setting values");
          System.out.println("Id = "+pt_emp2.getId());
          System.out.println("Name = "+pt_emp2.getName());
          System.out.println("Department = "+pt_emp2.getDepartment());
          System.out.println("Hours worked = "+pt_emp2.getTimeSheet());
    }
    
}
