 


/**
 * Write a description of class MojDatum here.
 * 
 * @author NightRain 
 * @version (a version number or a date)
 */
public class MojDatum {
    private int dDay = 0;
    private int dMonth = 0;
    private int dYear = 0;
    /**
     * Constructor for objects of class MojDatum
     */
    public MojDatum(int day, int month, int year) {
        if (0 < day && day <= 31 && 0 < month && month <= 12) {
            this.dDay = day;
            this.dMonth = month;
            this.dYear = year;
        } else {
            System.out.println ("Err: Invalid format of date!\n" + day + "." + month + "." + year + " -> is not valid!");
            System.out.println ("-------------------------------");
        }
    }
    
    public boolean jePriest() {
        int del4 = 0;
        int del100 = 0;
        int del400 = 0;
        boolean result;
        
        del4 = this.dYear % 4;
        del100 = this.dYear % 100;
        del400 = this.dYear % 400;
        
        if ((del4 == 0 && del100 != 0) || del400 == 0) {
            //System.out.println ("Year " + this.dYear + " -> IS a leap year!");
            //System.out.println ("-------------------------------");
            result = true;
        } else {
            //System.out.println ("Year " + this.dYear + " -> is NOT a leap year!");
            //System.out.println ("-------------------------------");
            result = false;
        }
        return result;
    }
    
    public int pocetDni(){
        int count = 0;
        switch (this.dMonth) {
        case 1:
            count = 31;
            break;
        case 2:
            if (this.jePriest()) {
                count = 29 ;
            } else {
                count = 28;
            }
            break;
        case 3:
            count = 31;
            break;
        case 4:
            count = 30;
            break;
        case 5:
            count = 31;
            break;
        case 6:
            count = 30;
            break;
        case 7:
            count = 31;
            break;
        case 8:
            count = 31;
            break;
        case 9:
            count = 30;
            break;
        case 10:
            count = 31;
            break;
        case 11:
            count = 30;
            break;
        case 12:
            count = 31;
            break;          
        }
    return count;
    }
    
    public void nextDay(){  
        // if the count of days is higher than the capacity of the month
        if (this.pocetDni() < this.dDay) {
            System.out.println ("Err: Invalid format of date!\n" + this.dDay + "." + this.dMonth + "." + this.dYear + " -> is not valid!");
            System.out.println ("-------------------------------");
        } else {
        
            if (this.pocetDni() == this.dDay) {
                this.dDay = 1;
                if (this.dMonth == 12) {
                    this.dMonth = 1;
                    this.dYear++;
                } else {
                    this.dMonth++;
                }
            } else {
                this.dDay++;
            }
            System.out.println ("Today is: " + this.dDay + "." + this.dMonth + "." + this.dYear);
            System.out.println ("--------------------------------");
        }
     
    
    }
}
