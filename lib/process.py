import sys
import matplotlib.pyplot as plt


def process_files(filename_array, savefile=None):

    scores = [[]]

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
                    signs_bits_trips_fit = (int(words[1]),
                                            int(words[4]),
                                            int(words[7]),
                                            float(words[10]))
                else:
                    signs_bits_trips_fit = (int(words[1]),
                                            int(words[4]),
                                            int(words[6]),
                                            float(words[9]))
                if gen >= 0:
                    scores[gen].append(signs_bits_trips_fit)
                    # print(signs_bits_trips_fit)
            elif line.startswith('GEN'):
                words = line.split(' ')
                gen = int(words[1])
                if len(scores) <= gen:
                    scores.append([])

    # trim incomplete entries
    pop_size = max([len(s) for s in scores])
    print('Total population is {}'.format(pop_size))
    scores = [s for s in scores if len(s) == pop_size]
    # print(scores)

    fig, axs = plt.subplots(2, 2)

    plot_spec = '.'
    for ii in range(pop_size):
        axs[0, 0].plot([s[ii][0] for s in scores], plot_spec, ms=2)
        axs[0, 1].plot([s[ii][1] for s in scores], plot_spec, ms=2)
        axs[1, 0].plot([s[ii][2] for s in scores], plot_spec, ms=2)
        axs[1, 1].plot([s[ii][3] for s in scores], plot_spec, ms=2)

    def average_trend(ii):
        return([sum([e[ii] for e in s])/pop_size for s in scores])

    axs[0, 0].plot(average_trend(0), 'k-')
    axs[0, 1].plot(average_trend(1), 'k-')
    axs[1, 0].plot(average_trend(2), 'k-')
    axs[1, 1].plot(average_trend(3), 'k-')

    axs[0, 0].set_title('Signs')
    axs[0, 1].set_title('Bits')
    axs[1, 0].set_title('Trips')
    axs[1, 1].set_title('Fitness')

    if savefile:
        print('Saving plot to {}'.format(savefile))
        fig.savefig(savefile, dpi=150)
    else:
        plt.show()


if __name__ == '__main__':
    process_files(sys.argv[1:])
