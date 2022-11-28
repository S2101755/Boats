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
public class Employee {
    //some variables
    int emp_id;
    String name;
    String dept;
    //constructor
    //a constructor is a specific function which build the class
    //one is an empty constructor 
    public Employee()
    {
       //empty
        //default constructor
    }
    //parameterized constructor
    public Employee(int id, String n, String d)
    {
        this.emp_id = id;
        this.name = n;
        this.dept = d;
    }
    //display
    public void display()
    {
        System.out.println("Id = "+this.emp_id);
        System.out.println("Name = "+this.name);
        System.out.println("Department = "+this.dept);
    }
    
}
