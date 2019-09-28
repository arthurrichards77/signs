import matplotlib.pyplot as plt

scores = []
while True:
  try:
    s = raw_input()
    sa=s.split(' ')
    mem = int(sa[1])
    scr = int(sa[-1])
    while len(scores)<mem:
      scores.append([])
    scores[mem-1].append(scr)
  except EOFError:
    print("End of input")
    break
max_scr = max([max(s) for s in scores])
print(max_scr)
for seq in scores:
  plt.plot(seq,'.')
plt.show()

