
package CustomerServiceCenter;

import java.util.ArrayList;

/**
 *
 * @author == Shauzab ==
 */

public class Customerservicecenter {

    private String name;
    private ArrayList<Computer> computers;
    private int jobSheetNumber;
    private String model;
    private String service_type;

    public Customerservicecenter(String name, int jobSheetModel, String model, String service_type) 
    {
        this.name = name;
        this.jobSheetNumber = jobSheetNumber;
        this.model = model;
        this.service_type = service_type;
        computers = new ArrayList();
    }

    public ArrayList<Computer> getComputers() 
    {
        return computers;
    }

    public void setComputers(ArrayList<Computers> computers) 
    {
        this.computers = computers;
    }

    public String getName() 
    {
        return name;
    }

    public void setName(String name) 
    {
        this.name = name;
    }
    
    public String getModel() 
    {
        return model;
    }
     
    public void setModel(String model) 
    {
        this.model = model;
    }
    
     public String getServiceType() 
     {
        return service_type;
    }
     
    public void setServiceType(String service_type) 
    {
        this.service_type = service_type;
    }
    
    
    public int getjobSheetNumber() 
    {
        return jobSheetNumber;
    }
     
    public void setjobSheetNumber(String jobSheetNumber)
    {
        this.jobSheetNumber = jobSheetNumber;
    }
    
    public void addComputer(Computers computer) 
    {
        computers.add(computer);
    }
    
    @Override
    public String toString() 
    {
        return "Customerservicecenter " + "Name" + name + ", model=" + model";
    }
}

