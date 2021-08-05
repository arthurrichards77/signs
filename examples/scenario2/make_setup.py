import os,sys
from random import seed, gauss, randrange, choice
sys.path.append(os.getcwd()+'/../../lib')
from sim_builder import SimBuilder

#repeatable but random!
seed(310520)

# Gaussian distribution truncated in the range
def clustered():
    x = int(gauss(64,20))
    if x<0:
        x=0
    elif x>127:
        x=127
    return(x)

def uniform():
    x = randrange(128)
    return(x)

gens = [clustered,uniform]

num_depots = 16
depot_locs = []
for i in range(num_depots):
    fx = choice(gens)
    fy = choice(gens)
    # print(fx,fy)
    loc=(fx(),fy())
    # print('Depot at {}'.format(loc))
    depot_locs.append(loc)

s = SimBuilder(128,128)

num_agents = 200

for i in range(num_agents):
    home_depot = choice(depot_locs)
    goal_list = []
    num_goals = randrange(2,20)
    for j in range(num_goals):
        next_goal = (randrange(128),
                     randrange(128))
        goal_list.append(next_goal)
        goal_list.append(home_depot)
    s.make_agent(home_depot, goal_list)