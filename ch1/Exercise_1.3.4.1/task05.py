a = (5, 24, -1982)                                # Python code for task 5
b = (5, 24, -1980)
c = (11, 13, -1983)
s = sorted({c, a, b})
for i in s:
    print(f'{i[1]} {i[0]} {-i[2]}')
