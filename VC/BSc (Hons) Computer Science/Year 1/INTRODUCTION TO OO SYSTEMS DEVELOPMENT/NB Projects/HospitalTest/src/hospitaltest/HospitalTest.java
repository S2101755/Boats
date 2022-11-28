
package hospitaltest;

import java.util.ArrayList;

/**
 *
 * @author ShauXab
 */
public class HospitalTest {

    public static void main(String[] args) {
        
        doctors doctor = new doctors();

        doctor.drID = 11022;
        doctor.drName = "Ali";
        doctor.drDep = "ER";
        doctor.drSpec = "Surgeon";
        doctor.drSpec.length();
        
        System.out.println("Doctor ID :: "+doctor.drID + "\nDoctor Name :: "+doctor.drName + "\nDoctor Department :: "+doctor.drDep + "\nSpeciality Doctor? :: "+doctor.drSpec);
        
        
        
        }
    }
    
    class doctors {
        int drID;
        String drName;
        String drDep;
        String drSpec;

      
}
    
