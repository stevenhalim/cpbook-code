import java.util.*;
import java.io.*;

class ch6_01_basic_string {
  static int isvowel(char ch) { // make sure ch is in lowercase
    String vowel = "aeiou";
    for (int j = 0; j < 5; j++)
      if (vowel.charAt(j) == ch)
        return 1;
    return 0;
  }

  public static void main(String[] args) throws Exception {
    int i, pos, digits, alphas, vowels, consonants;
    Boolean first, prev_dash, this_dash;
    String str = "";
    first = true; // technique to differentiate first line with the other lines
    prev_dash = this_dash = false; // to differentiate whether the previous line contains a dash or not

    File f = new File("ch6.txt");
    Scanner sc = new Scanner(f);
    while (sc.hasNext()) {
      String line = sc.nextLine();
      if (line.equals(".......")) break;
      if (line.charAt(line.length() - 1) == '-') {
        line = line.substring(0, line.length() - 1); // if the last character is '-', delete it
        this_dash = true;
      }
      else
        this_dash = false;
      if (!first && !prev_dash)
        str = str + " "; // only append " " if this line is the second one onwards
      first = false;
      str = str + line;
      prev_dash = this_dash;
    }

    char[] temp = str.toCharArray();
    for (i = digits = alphas = vowels = consonants = 0; i < str.length(); i++) { // we can use str[i] as terminating condition as string in C++ is also terminated with NULL (0)
      temp[i] = Character.toLowerCase(temp[i]); // make each character lower case
      digits += Character.isDigit(temp[i]) ? 1 : 0;
      alphas += Character.isLetter(temp[i]) ? 1 : 0;
      vowels += isvowel(temp[i]); // already returns 1 or 0
    }
    consonants = alphas - vowels;
    str = new String(temp);
    System.out.println(str);
    System.out.printf("%d %d %d\n", digits, vowels, consonants);
    int hascs3233 = (str.indexOf("cs3233") != -1) ? 1 : 0;

    Vector<String> tokens = new Vector<String>();
    TreeMap<String, Integer> freq = new TreeMap<String, Integer>();
    StringTokenizer st = new StringTokenizer(str, " .");
    while (st.hasMoreTokens()) {
      String p = st.nextToken();
      tokens.add(p);
      if (!freq.containsKey(p)) freq.put(p, 1);
      else                      freq.put(p, freq.get(p) + 1);
    }

    Collections.sort(tokens);
    System.out.println(tokens.get(0) + " " + tokens.get(tokens.size() - 1));
    System.out.printf("%d\n", hascs3233);

    int ans_s = 0, ans_h = 0, ans_7 = 0;
    String lastline = sc.nextLine();
    for (i = 0; i < lastline.length(); i++) {
      char ch = lastline.charAt(i);
           if (ch == 's') ans_s++;
      else if (ch == 'h') ans_h++;
      else if (ch == '7') ans_7++;
    }
    System.out.printf("%d %d %d\n", ans_s, ans_h, ans_7);
  }
}
