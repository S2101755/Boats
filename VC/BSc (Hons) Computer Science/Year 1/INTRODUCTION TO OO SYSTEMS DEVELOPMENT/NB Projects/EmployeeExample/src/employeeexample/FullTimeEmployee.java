/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package employeeexample;

/**
 *
 * @author CompLab3
 */
public class FullTimeEmployee extends Employee{
    //by keeping extends means FullTimeEmployee is a child of Employee class
    //a specific variable
    double basic_salary;
    //a constructor for this class
    //a paraterized constructor
    public FullTimeEmployee(int id, String n, String d, double bsalary)
    {
        super(id,n,d);
        this.basic_salary = bsalary;
    }
    //display method again
    @Override
    public void display()
    {
        super.display();
        System.out.println("Basic Salary = "+basic_salary);
        
    }
    
    
}
