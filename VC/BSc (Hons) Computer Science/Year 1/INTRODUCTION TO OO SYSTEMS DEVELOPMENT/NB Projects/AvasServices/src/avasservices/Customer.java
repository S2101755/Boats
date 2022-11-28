
package avasservices;

/**
 *
 * @author ShauXab
 */
public class Customer {
    
    String custName;
    int custMNum;
    String custAddress;
    String boardNum;
    
    
    Customer(String cusName, int cMN, String cAddr, String bNum){
        this.custName = cusName;
        this.custMNum = cMN;
        this.custAddress = cAddr;
        this.boardNum = bNum;
    }
    
    //Gett
    public String custName(){
        return custName;
    }
      public int custMNum(){
        return custMNum;
    }
      public String custAddress(){
      return custAddress;
    }
      public String boardNum(){
      return boardNum;
    }
      
      //Sett
    public void setcustName(String cusName){
    this.custName = cusName;
    }  
    
    public void setcustMNum(int cMN){
    this.custMNum = cMN;
    }  
    public void setcustAddress(String cAddr){
    this.custAddress = cAddr;
    }  
    public void setboardNum(String bNum){
    this.boardNum = bNum;
    }  
}
