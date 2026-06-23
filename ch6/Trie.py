def norm_codepoint(s: str, base: int = ord("A")) -> int:
    """Return integer represening normalized codepoint for a given base."""
    return ord(s)-base

class Vertex:
    def __init__(self, ch: str):
        self.alphabet = ch
        self.exist = False
        self.child = [None] * 26

class Trie:
    def __init__(self):
        self.root = Vertex("!")

    def insert(self, word: str) -> None:
        cur = self.root
        for char in word:
            alpha_num = norm_codepoint(char)
            current_child = cur.child[alpha_num]
            # If current_child is None, set cur as new Vertex instance.
            cur = current_child or Vertex(char)
        cur.exist = True

    def search(self, word: str) -> bool:
        cur = self.root
        for char in word:
            alpha_num = norm_codepoint(char)
            current_child = cur.child[alpha_num]
            if not current_child:
                return False
            cur = current_child
        return cur.exist

    def starts_with(self, prefix: str) -> bool:
        cur = self.root
        for char in prefix:
            alpha_num = norm_codepoint(char)
            current_child = cur.child[alpha_num]
            if not current_child:
                return False
            cur = current_child
        return True


if __name__ == "__main__":
    t = Trie()
    words = "CAR", "CAT", "RAT"
    for word in words:
        print("Inserting: ", word)
        t.insert(word)

    print()

    prefixes = "CA", "Z", "AT"
    results = map(t.starts_with, prefixes)
    for prefix, result in zip(prefixes, results):
        print(f"""Starts with "{prefix}" exist? {result}""")

    print()

    print(f""""CAR" exist? {t.search(words[0])}""")
    print(f""""DOG" exist? {t.search("DOG")}""")
