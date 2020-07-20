import java.util.*;

class vertex {
  public char alphabet;
  public Boolean exist;
  public ArrayList<vertex> child;

  public vertex(char a) {
    alphabet = a;
    exist = false;
    child = new ArrayList<>(Collections.nCopies(26, null));
  }
};

class Trie {                                     // this is TRIE
  private vertex root;                           // NOT Suffix Trie

  public Trie() { root = new vertex('!'); }

  public void insert(String word) {              // insert a word into trie
    vertex cur = root;
    for (int i = 0; i < word.length(); ++i) {    // O(n)
      int alphaNum = word.charAt(i)-'A';
      if (cur.child.get(alphaNum) == null)       // add new branch if null
        cur.child.set(alphaNum, new vertex(word.charAt(i)));
      cur = cur.child.get(alphaNum);
    }
    cur.exist = true;
  }

  public Boolean search(String word) {           // true if word in trie
    vertex cur = root;
    for (int i = 0; i < word.length(); ++i) {    // O(m)
      int alphaNum = word.charAt(i)-'A';
      if (cur.child.get(alphaNum) == null)       // not found
        return false;
      cur = cur.child.get(alphaNum);
    }
    return cur.exist;                            // check exist flag
  }

  public Boolean startsWith(String prefix) {     // true if match prefix
    vertex cur = root;
    for (int i = 0; i < prefix.length(); ++i) {
      int alphaNum = prefix.charAt(i)-'A';
      if (cur.child.get(alphaNum) == null)       // not found
        return false;
      cur = cur.child.get(alphaNum);
    }
    return true;                                 // reach here, return true
  }

  public static void main(String[] args) {
    Trie T = new Trie();
    TreeSet<String> S = new TreeSet<>() {{ add("CAR"); add("CAT"); add("RAT"); }};
    for (String str : S) {
      System.out.printf("Insert %s\n", str);
      T.insert(str);
    }
    System.out.printf("'CAR' exist? %d\n", T.search("CAR") ? 1 : 0); // 1 (true)
    System.out.printf("'DOG' exist? %d\n", T.search("DOG") ? 1 : 0); // 0 (false)
    System.out.printf("Starts with 'CA' exist? %d\n", T.startsWith("CA") ? 1 : 0); // 1 (true)
    System.out.printf("Starts with 'Z' exist? %d\n", T.startsWith("Z") ? 1 : 0); // 0 (false)
    System.out.printf("Starts with 'AT' exist? %d\n", T.startsWith("AT") ? 1 : 0); // 0 (false) for this Trie, but in a Suffix Trie, we have a suffix "AT" (from "CAT" or "RAT") that starts with "AT"
  }
};
