import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import os
from matplotlib.colors import Normalize




wpath = Path(__file__).resolve().parent


def get_time_from_file(fname):
    with open(fname, 'r') as f:
        line_one = f.readline()
    return float(line_one[7:])




x = np.linspace(0, 10, 200)
y = np.linspace(0, 8, 200)

if not(Path.is_dir(Path(wpath, 'images'))):
    Path.mkdir(Path(wpath, 'images'))

if not(Path.is_dir(Path(wpath, 'images/density_images'))):
    Path.mkdir(Path(wpath, 'images/density_images'))

os.system(f"rm {Path(wpath, 'images/density_images', '*')}")


for i in range(300):
    filename = Path(wpath, f"drop/density/density_time_iter_{i}.txt")
    data_to_plot = np.loadtxt(filename)
    time = get_time_from_file(filename)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 8)
    ax.set_title(f'time {time:.2f}')
    pcm = ax.pcolormesh(x, y, data_to_plot, cmap="Blues", norm=Normalize(vmin=0, vmax=70))
    fig.colorbar(pcm)
    plt.savefig(Path(wpath, f'images/density_images/img_{i:04d}.jpg'), dpi=400)
    
os.system(f"gm convert -delay 10 -loop 0 {Path(wpath, 'images/density_images', 'img_*.jpg')} {Path(wpath, 'images/density.gif')}")