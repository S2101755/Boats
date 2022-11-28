package CustomerBill;

import java.util.ArrayList;

/**
 *
 * @author == Shauzab ==
 */

public class Customerbill {

   private int Bill_no;
    private int Date;
    private int price;
    private int quantity;
    private ArrayList<Item> items;

    public Customerbill (int Bill_no, int Date) 
    {
        this.Bill_no = Bill_no;
        this.Date = Date;
        this.price = price;
        this.quantity = quantity;
        items = new ArrayList();
    }

    public ArrayList<Item> getItem() 
    {
        return items;
    }

    public void setPrice(ArrayList<Item> items) 
    {
        this.items = price;
    }

    public void setQuantity(ArrayList<Item> items) 
    {
        this.items = quantity;
    }

    public int getBill_no() 
    {
        return Bill_no;
    }

    public void setBillno(String Bill_no) 
    {
        this.Bill_no = Bill_no;
    }
    
    public int Date() 
    {
        return Date;
    }
    
    public void addItems(Items item) 
    {
        items.add(item);
    }
    
    public int totalBill() 
    {
        int total = 0;
        for (Items i : item) {
            total += price * quantity;
        }
        return total;
    }

   
    @Override
    public String toString() 
    {
        return "Customerbill " + "Bill_no" + Bill_no + ", Date=" + Date + ", items=" + items + "";

    }
    
}
