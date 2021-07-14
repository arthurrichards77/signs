import matplotlib.pyplot as plt
import sys
scores = []

file_name = sys.argv[1]
file_hdl = open(file_name, 'r')

gen = -1
scores = [[]]

while True:
  line = file_hdl.readline()
  if not line:
    break
  #print(line)
  if line.startswith('Eva'):
    words = line.split(' ')
    if len(words)==11:
      signs_bits_trips_fit = (int(words[1]),
                              int(words[4]),
                              int(words[7]),
                              float(words[10]))
    else:
      signs_bits_trips_fit = (int(words[1]),
                              int(words[4]),
                              int(words[6]),
                              float(words[9]))
    if gen>=0:
      scores[gen].append(signs_bits_trips_fit)
    #print(signs_bits_trips_fit)
  elif line.startswith('GEN'):
    words = line.split(' ')
    gen = int(words[1])
    scores.append([])
#print(scores)

# trim incomplete entries
pop_size = max([len(s) for s in scores])
#print(pop_size)
scores = [s for s in scores if len(s)==pop_size]
#print(scores)

fig,axs = plt.subplots(2,2)
for ii in range(pop_size):
  axs[0,0].plot([s[ii][0] for s in scores],'.')
  axs[0,1].plot([s[ii][1] for s in scores],'.')
  axs[1,0].plot([s[ii][2] for s in scores],'.')
  axs[1,1].plot([s[ii][3] for s in scores],'.')
axs[0,0].set_title('Signs')
axs[0,1].set_title('Bits')
axs[1,0].set_title('Trips')
axs[1,1].set_title('Fitness')
plt.show()

exit()

while True:
  try:
    s = input()
    sa=s.split(' ')
    print(sa)
    mem = int(sa[1])
    scr = float(sa[-1])
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

