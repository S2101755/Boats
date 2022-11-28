package com.naaih.computerservicecenter;

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
//A ComputerServiceCenter has a name and a list of computers (taken for service). 
//Each Computer has a jobSheetNumber, model and a service_type (eg: OSreinstalling, virusScanning). 
//ComputerServiceCenter also has a method (ComputerForScan) to count the number of computers brought for 
//virus scan (i.e. a method which takes a string parameter (ignore case) and returns a number).
