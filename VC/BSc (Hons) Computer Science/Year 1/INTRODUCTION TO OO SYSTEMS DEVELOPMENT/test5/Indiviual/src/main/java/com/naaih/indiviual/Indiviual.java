package com.naaih.indiviual;

import java.util.ArrayList;

public class Indiviual {

    private String name;
    private String description;
    private int cost;
    private ArrayList<EntryCoupon> entryCoupon;
    private String Activity;
    private boolean canParticipate;

    public Indiviual(String name) {
        this.name = name;
        entryCoupon = new ArrayList();
    }

    public Activity(String description, int cost) {
        this.Activity = Activity;
        this.description = description;
        this.cost = cost;
    }

    public ArrayList<EntryCoupon> getEntryCoupon() {
        return entryCoupon;
    }

    public String getName() {
        return name;
    }

    public void setLocation(String name) {
        this.name = name;
    }

    public String getActivity() {
        return name;
    }

    public void setActivity(String Activity) {
        this.Activity = description;
    }

    public void setActivity(String Activity) {
        this.Activity = cost;
    }

    public void setActivity(String Activity) {
        this.Activity = Activity;
    }

    public void addFlight(EntryCoupon entryCoupon) {
        entryCoupon.add(entryCoupon);
    }

    public boolean canParticipate(String Activity) {

    }

    public boolean canParticipate(String Activity) {
        for (int i = 0; i < price.size(); i++) {
            if (price.get(i).Activity.toLowerCase() == .Activity()) {
                return true;
            }
        }
        return false;
    }
    
    @Override
    public String toString()
    {
        return "Indiviual{" + "name" + name + " , Activity " + Activity"};

    }
}