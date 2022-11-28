/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package feelburgercafe;

/**
 *
 * @author shifaz
 */
public class FoodOrder {

    public FoodOrder(FoodItem item, String deliveryAddress) {
        this.item = item;
        this.deliveryAddress = deliveryAddress;
    }
    FoodItem item;
    String deliveryAddress;
}
