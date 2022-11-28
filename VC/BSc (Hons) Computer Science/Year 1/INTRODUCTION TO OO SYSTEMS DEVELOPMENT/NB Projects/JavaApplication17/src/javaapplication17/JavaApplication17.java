/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javaapplication17;

import java.util.ArrayList;

public class CustomerServiceCenter {

    private String name;
    private ArrayList<Computer> computers;
    private int jobSheetNumber;
    private String model;
    private String service_type;

    public CustomerServiceCenter(String name, int jobSheetModel, String model, String service_type) {
        this.name = name;
        this.jobSheetNumber = jobSheetNumber;
        this.model = model;
        this.service_type = service_type;
        computers = new ArrayList();
    }

    public ArrayList<Computer> getComputers() {
        return computers;
    }

    public void setFlights(ArrayList<Computers> computers) {
        this.computers = computers;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    
    public String getModel() {
        return model;
    }
     
    public void setName(String model) {
        this.model = model;
    }
    
     public String getServiceType() {
        return service_type;
    }
     
    public void setServiceType(String service_type) {
        this.service_type = service_type;
    }
    
    
    public int getjobSheetNumber() {
        return jobSheetNumber;
    }
     
    public void setjobSheetNumber(String jobSheetNumber) {
        this.jobSheetNumber = jobSheetNumber;
    }
    
    public void addComputer(Computers computer) {
        computers.add(computer);
    }
    
    @Override
    public String toString() {
        return "CustomerServiceCenter{" + "Name" + name + ", model=" + model}";
    }
}