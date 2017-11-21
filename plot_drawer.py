import matplotlib.pyplot as plt
import numpy as np

x = np.array([1,2,4,8,16,32])
y = np.array([186759100, 80408312, 99001145, 95171506, 64264311, 27624234])


x_plot = range(len(y))
plt.plot(x_plot, y, 'bo')
plt.xticks(x_plot, x)
plt.xlabel('# of threads')
plt.ylabel('# of updates')
plt.show()
