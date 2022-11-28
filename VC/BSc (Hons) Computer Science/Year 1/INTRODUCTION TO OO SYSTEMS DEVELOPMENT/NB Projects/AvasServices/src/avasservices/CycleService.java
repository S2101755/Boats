
package avasservices;

/**
 *
 * @author ShauXab
 */
public class CycleService {
    
    String cycleName;
    String cycleBrand;
    int Price;
    
    
    CycleService (String cBrand, String cName, int price){
        this.cycleName = cName;
        this.cycleBrand = cBrand;
        this.Price = price;
    }
    
    //Gett
    public String getcycleName(){
        return cycleName;
    }
    
    public String setcycleBrand(){
        return cycleBrand;
    }
        
    public int setprice(){
    return Price;        
    }
    //Sett
    public void setcycleName(String cName){
        this.cycleName = cName;
    }
    
    public void setcycleBrand(String cBrand){
        this.cycleBrand = cBrand;
    }
    
    public void setprice(int price){
        this.Price = price;
    }
    
}
