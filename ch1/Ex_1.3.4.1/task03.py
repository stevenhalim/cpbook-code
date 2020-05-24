from datetime import date                        # Python code for task 3
s = date(2010, 8, 9)                             # CP1 launch date
t = date.today()
print(s.strftime("%a"))                          # 'Mon', %A for 'Monday'
print("{} day(s) ago".format((t-s).days))        # ans grows over time
