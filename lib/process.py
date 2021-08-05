import sys
import matplotlib.pyplot as plt
import numpy as np

def process_files(filename_array, savefile=None):

    scores = [[]]
    baseline = None

    for file_name in filename_array:
        print('Processing file {}'.format(file_name))
        file_hdl = open(file_name, 'r')

        gen = -1

        while True:
            line = file_hdl.readline()
            if not line:
                break
            # print(line)
            if line.startswith('Eva'):
                words = line.split(' ')
                if len(words) == 11:
                    signs_bits_trips_fit_gen = (int(words[1]),
                                                int(words[4]),
                                                int(words[7]),
                                                float(words[10]),
                                                gen)
                    baseline = signs_bits_trips_fit_gen
                else:
                    signs_bits_trips_fit_gen = (int(words[1]),
                                                int(words[4]),
                                                int(words[6]),
                                                float(words[9]),
                                                gen)
                if gen >= 0:
                    # print(gen,len(scores))
                    scores[gen].append(signs_bits_trips_fit_gen)
                    # print(signs_bits_trips_fit)
            elif line.startswith('GEN'):
                words = line.split(' ')
                gen = int(words[1])
                if len(scores) <= gen:
                    scores.append([])
        print('Read {} generations'.format(gen))

    fig, axs = plt.subplots(2, 2)

    num_gens = len(scores)
    gens = range(num_gens)
    # axs[0, 0].plot(gen_list,
    #                [s[0] for s in scores], plot_spec, ms=1)
    # axs[0, 1].plot(gen_list,
    #                [s[1] for s in scores], plot_spec, ms=1)
    # axs[1, 0].plot(gen_list,
    #                [s[2] for s in scores], plot_spec, ms=1)
    # axs[1, 1].plot(gen_list,
    #                [s[3] for s in scores], plot_spec, ms=1)

    def average_trend(ii, power=1):
        aves = [sum([e[ii]**power for e in g])/len(g) for g in scores]
        return(np.array(aves))

    def max_trend(ii):
        return([max([e[ii] for e in g]) for g in scores])

    def min_trend(ii):
        return([min([e[ii] for e in s]) for s in scores])

    def mean_stdv(ii):
        aves = average_trend(ii)
        avesq = average_trend(ii, 2)
        stdvs = np.sqrt(avesq - aves*aves)
        return(aves, stdvs)

    def makeplot(ax, ii):
        aves, stdvs = mean_stdv(ii)
        ax.fill_between(gens,
                        aves + stdvs,
                        aves - stdvs)
        ax.plot(gens, aves, 'k:')
        ax.plot(max_trend(ii), 'm-')
        ax.plot(min_trend(ii), 'm-')
        ax.plot([0, num_gens],
                [baseline[ii], baseline[ii]], 'k--')
        ax.plot(0, 0, 'w.')

    makeplot(axs[0, 0], 0)
    makeplot(axs[0, 1], 1)
    makeplot(axs[1, 0], 2)
    makeplot(axs[1, 1], 3)

    axs[0, 0].set_ylabel('Signs')
    axs[0, 1].set_ylabel('Bits')
    axs[1, 0].set_ylabel('Trips')
    axs[1, 1].set_ylabel('Fitness')
    axs[1, 0].set_xlabel('Generation')
    axs[1, 1].set_xlabel('Generation')

    fig.tight_layout(w_pad=1.0)

    if savefile:
        print('Saving plot to {}'.format(savefile))
        fig.savefig(savefile, dpi=150)
    else:
        plt.show()


if __name__ == '__main__':
    process_files(sys.argv[1:])
