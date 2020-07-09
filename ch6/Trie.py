class vertex:
  def __init__(self, chr: str):
    self.alphabet = chr
    self.exist = False
    self.child = [None] * 26

class Trie:
  def __init__(self):
    self.root = vertex('!')

  def insert(self, word):
    cur = self.root
    for w in word:
      alphaNum = ord(w)-ord('A')
      if cur.child[alphaNum] == None:
        cur.child[alphaNum] = vertex(w)
      cur = cur.child[alphaNum]
    cur.exist = True

  def search(self, word):
    cur = self.root
    for w in word:
      alphaNum = ord(w)-ord('A')
      if cur.child[alphaNum] == None:
        return False
      cur = cur.child[alphaNum]
    return cur.exist

  def startsWith(self, prefix):
    cur = self.root
    for w in prefix:
      alphaNum = ord(w)-ord('A')
      if cur.child[alphaNum] == None:
        return False
      cur = cur.child[alphaNum]
    return True


def main():
  T = Trie()
  S = ['CAR', 'CAT', 'RAT']
  for s in S:
    print('Insert', s)
    T.insert(s)

  print('\'CAR\' exist?', T.search("CAR"))
  print('\'DOG\' exist?', T.search("DOG"))
  print('Starts with \'CA\' exist?', T.startsWith("CA"))
  print('Starts with \'Z\' exist?', T.startsWith("Z"))
  print('Starts with \'AT\' exist?', T.startsWith("AT"))


main()
