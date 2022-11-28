package t4.q1;

/**
 *
 * @author == Shauzab ==
 * 
 */
public class T4Q1 {

    public static void main(String[] args) {
        // Program Code
        
        String str = "The,Atlantic,Ocean,is,home,to,a,diverse,array,of,sea,life,both,those,we,can,observe,at,the,surface,and,those,all,but,hidden,from,human,eyes";
        
        String[] words = str.split(",");
        
        for (String w:words) 
        {
            System.out.println(w);
        }
    }
    
}
