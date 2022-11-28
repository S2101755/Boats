package hospital;

import java.util.ArrayList;

/**
 *
 * @author == Shauzab ==
 * 
 */

public class Hospital {

    private String name;
    private String address;
    private String speciality;
    private ArrayList<Doctor> doctors;

    public Hospital(String name, String address) {
        this.name = name;
        this.address = address;
        doctors = new ArrayList();
    }

    public ArrayList<Doctor> getDoctors() {
        return doctors;
    }

    public void setDoctors(ArrayList<Doctor> Doctors) {
        this.doctors = doctors;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void addDoctors(Doctors doctors) {
        doctors.add(doctors);
    }

    public boolean checkSpeciality(String speciality) {
        for (int i = 0; i < doctors.size(); i++) {
            if (doctors.get(i).speciality.toLowerCase() == speciality.toLowerCase()) {
                return true;
            }
        }
        return false;
    }
    
    @Override
    public String toString() {
        return "Hospital " + "Name" + name + ", address=" + address
                + ", Doctors=" + doctors + '';
    }

    }
    
