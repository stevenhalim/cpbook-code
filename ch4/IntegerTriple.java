class IntegerTriple implements Comparable {
  Integer _first, _second, _third;

  public IntegerTriple(Integer f, Integer s, Integer t) {
    _first = f;
    _second = s;
    _third = t;
  }

  public int compareTo(Object o) {
    if (!this.first().equals(((IntegerTriple)o).first()))
      return this.first() - ((IntegerTriple)o).first();
    else if (!this.second().equals(((IntegerTriple)o).second()))
      return this.second() - ((IntegerTriple)o).second();
    else
      return this.third() - ((IntegerTriple)o).third();
  }

  Integer first() { return _first; }
  Integer second() { return _second; }
  Integer third() { return _third; }

  public String toString() { return first() + " " + second() + " " + third(); }
}
