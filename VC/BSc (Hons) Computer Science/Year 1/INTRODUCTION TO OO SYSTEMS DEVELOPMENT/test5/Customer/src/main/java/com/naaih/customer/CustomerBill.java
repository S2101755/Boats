package com.naaih.customer;

import java.util.ArrayList;

public class CustomerBill {

    private int Bill_no;
    private int Date;
    private int price;
    private int quantity;
    private ArrayList<Item> items;

    public CustomerBill(int Bill_no, int Date) {
        this.Bill_no = Bill_no;
        this.Date = Date;
        this.price = price;
        this.quantity = quantity;
        items = new ArrayList();
    }

    public ArrayList<Item> getItem() {
        return items;
    }

    public void setFlights(ArrayList<Item> items) {
        this.items = price;
    }

    public void setFlights(ArrayList<Item> items) {
        this.items = quantity;
    }

    public int getBill_no() {
        return Bill_no;
    }

    public void setLocation(String Bill_no) {
        this.Bill_no = Bill_no;
    }
    
    public int Date() {
        return Date;
    }
    
    public void addItems(Items item) {
        items.add(item);
    }
    
    public int totalBill() {
        int total = 0;
        for (Items i : item) {
            total += price * quantity;
        }
        return total;
    }

   
    @Override
    public String toString() {
        return "CustomerBill{" + "Bill_no" + Bill_no + ", Date=" + Date
                + ", items=" + items + '}';

    }
}

// A CustomerBill class has 3 properties of bill_no, 
// a date and items which is a list of items sold. Each item has quantity and price.
// The CustomerBill constructor takes the bill_no and location and also has a method called totalBill() 
// which returns quantity * price for each selected item. 
