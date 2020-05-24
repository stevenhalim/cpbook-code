import java.util.*;                              // Java code for task 3
class Main {
  public static void main(String[] args) {
    String[] names = new String[]
      { "", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    Calendar that_day = new GregorianCalendar(2010, 7, 9); // 9 August 2010
    // note that month starts from 0, so we need to put 7 instead of 8
    System.out.println(names[that_day.get(Calendar.DAY_OF_WEEK)]); // "Mon"
    long today = new Date().getTime(); // today
    long diff = (today - that_day.getTime().getTime()) / (24*60*60*1000);
    System.out.println(diff + " day(s) ago"); // ans grows over time
  }
}
