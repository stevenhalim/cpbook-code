import sys

events = []

def can(f: float):
  global events

  cur_d, cur_n, leak_rate, dt = 0, 0, 0, 0
  original_f = f

  for i in range(len(events)):
    dt = events[i][0] - cur_d
    f -= dt / 100 * cur_n
    f -= dt * leak_rate
    if f < 0:
      return False
    if events[i][1] <= 0:
      cur_n = -events[i][1]
    elif events[i][1] == 1:
      leak_rate += 1
    elif events[i][1] == 2:
      f = original_f
    elif events[i][1] == 3:
      leak_rate = 0
    elif events[i][1] == 4:
      break
    cur_d = events[i][0]
  return f >= 0.0


if __name__ == '__main__':
  for line in sys.stdin:
    n = int(line.split()[-1])
    if n == 0:
      break
    events = [[0, -n]]

    while True:
      tkn = sys.stdin.readline().strip('\n').split()
      d = int(tkn[0])
      state = ' '.join(tkn[1:])
      if state[0:4] == 'Fuel':
        n = int(tkn[-1])
        events.append([d, -n])
      elif state == 'Leak':
        events.append([d, 1])
      elif state == 'Gas station':
        events.append([d, 2])
      elif state == 'Mechanic':
        events.append([d, 3])
      elif state == 'Goal':
        events.append([d, 4])
        break

    lo, hi = 0.0, 10000.0
    for i in range(50):
      mid = (lo+hi)/2
      if can(mid):
        hi = mid
      else:
        lo = mid

    print('%.3lf' % hi)
