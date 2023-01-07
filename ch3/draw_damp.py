import numpy as np;
import matplotlib.pyplot as plt

def draw_damp(data):
    x_data = [i for i in range(0, len(data))]
    plt.plot(x_data, data, linestyle='-', marker='o', color='blue')
    # plt.xlim(0, len(data) - 1)
    plt.xticks(x_data)
    plt.show()


if __name__ == "__main__":
    data = [0.001, 0.002, 0.008, 0.064, 1.024, 32.768, 2097.15,
        699.051, 1398.1, 5592.41,
        1864.14, 1242.76,
        414.252,
        138.084,
        46.028,
        15.3427,
        5.11423,
        1.70474,
        0.568247,
        0.378832]
    draw_damp(data)