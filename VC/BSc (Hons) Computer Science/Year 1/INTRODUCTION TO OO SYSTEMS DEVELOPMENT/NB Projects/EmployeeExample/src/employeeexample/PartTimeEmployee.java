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
public class PartTimeEmployee extends Employee{
    //local variable
    int timesheetHours;
    //construtor
    public PartTimeEmployee()
    {
        //empty
    }
    //full parameterzed constructor   
    public PartTimeEmployee(int i, String n, String d, int t_sheet_hours)
    {
        super(i,n,d);
        this.timesheetHours = t_sheet_hours;
    }
    //part parameterized constructor
    public PartTimeEmployee(int i, String n, String d)
    {
        super(i,n,d);
      
    }
    //getter
    //show or return values
    public int getId()
    {
       return super.emp_id; //display the id of the object, reading
    }
    public String getName()
    {
       return super.name; //display the name of the object, reading
    }
    public String getDepartment()
    {
       return super.dept; //display the dept of the object, reading
    }
    public int getTimeSheet()
    {
       return this.timesheetHours; //display the time sheet hours of the object, reading
    }
    //setter
    //assign values 
    public void setId(int i)
    {
        super.emp_id = i;
    }
    public void setName(String n)
    {
        super.name = n;
    }
    public void setDepartment(String d)
    {
        super.dept = d;
    }
    public void setTimeSheet(int hours)
    {
        this.timesheetHours = hours;
    }
}
