# You should put this python file, the executable file and model file under the same directory
# I presume that the name of the executable file is 'denoiser.exe'
import os
import matplotlib.pyplot as plt
import numpy as np

dir = os.listdir()
sigmas = [0.01, 0.05, 0.1, 0.5, 0.8, 1.0, 2.0]

ind = np.arange(len(sigmas))
for filename in dir:
    ext = os.path.splitext(filename)[1]
    model_name = os.path.splitext(filename)[0]
    if ext == '.obj':
        error1 = []
        error2 = []
        time1 = []
        iterations = []
        error_bef = 34326.0
        error_now = 0
        for sigma in sigmas:
            itr = 0
            error_bef = 34326.0
            error_now = 34325.0
            while error_bef > error_now:
                itr = itr + 1
                error_bef = error_now
                command = "denoiser.exe" + " 0 " + filename + " " + str(sigma) + " " + str(itr)
                os.system(command)
                with open(model_name + ".out") as f:
                    for line in f:
                        data = line.split(' ')
                        error_now = float(data[1])
            with open(model_name + ".out") as f:
                for line in f:
                    data = line.split(' ')
                    iterations.append(itr)
                    error1.append(float(data[0]))
                    error2.append(float(data[1]))
                    time1.append(data[2])
        # plot the bar chart
        error1 = np.array(error1)
        error2 = np.array(error2)
        maxv = np.maximum(error1, error2)
        plt.ylabel('Errors(angle)')
        plt.xlabel('sigma')
        plt.title('Denoised Error(MSAE measurement)')
        width = 0.25
        p0 = plt.bar(ind + width / 2, error1, width, label = 'Noisy')
        p1 = plt.bar(ind - width / 2, error2, width, label = 'Denoised(Bilateral)')
        plt.xticks(ind, [str(x) for x in sigmas])
        plt.legend((p0[0], p1[0]), ('Noisy', 'Denoised' ))
        for x,y in enumerate(maxv):
            plt.text(x - width / 2, y + 0.1, str(time1[x]), va = 'center')
            plt.text(x - width / 2, y / 2, str(iterations[x]), va = 'center')
        axis = plt.axis()
        plt.axis([axis[0], axis[1], axis[2], 1.5 * axis[3]])
        plt.savefig(model_name +   ".png")
        plt.clf()