lineCounter = 0

def canPlace(r, c):
	for prev in range(c):
		if row[prev] == r or abs(row[prev] - r) == abs(prev - c):
			return False
	return True

def backtrack(c):
	if c == 8 and row[b] == a:  # candidate sol, (a, b) has 1 Queen
		global lineCounter
		print("%2d      %d" % (lineCounter + 1, row[0] + 1), end='')
		for j in range(1, 8):
			print(" %d" % (row[j] + 1), end='')
		print()
		lineCounter += 1
	for r in range(8):                          # try all possible row
		if ((c == b) & (r != a)):               # early pruning if row[b] != a
			continue;                           
		if (canPlace(r, c)):                    # if can place a Queen at this rol and row
			row[c] = r
			backtrack(c + 1)        # put this Queen here and recurse


def main():
	global row, lineCounter
	TC = int(input())
	while TC != 0:
		global a, b
		a = 1
		b = 1
		input()
		a, b = map(int, input().split())
		a -= 1                  # switch to 0-based indexing
		b -= 1
		lineCounter = 0
		row = [0, 0, 0, 0, 0, 0, 0, 0]
		print("SOLN       COLUMN")
		print(" #      1 2 3 4 5 6 7 8\n")
		backtrack(0)
		TC -= 1
		if TC != 0:
			print()

if __name__ == '__main__':
	main()
