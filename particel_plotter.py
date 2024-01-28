import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path
import os


wpath = Path(__file__).resolve().parent
data = np.loadtxt(Path(wpath, 'drop/position_evo.txt'))

time = data[::2, 0]
positions = data[:, 1:]
iterations = time.size
t_start = 0
t_stop = 20

if not(Path.is_dir(Path(wpath, 'images'))):
    Path.mkdir(Path(wpath, 'images'))

if not(Path.is_dir(Path(wpath, 'images/particle_images'))):
    Path.mkdir(Path(wpath, 'images/particle_images'))

os.system(f"rm {Path(wpath, 'images/particle_images', '*')}")

for i in range(iterations):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 8)
    ax.set_title(f'time {time[i]:.2f}')
    x_points = positions[2 * i, :]
    y_points = positions[2 * i + 1, :]
    ax.scatter(x_points, y_points, marker='.', s=3)
    plt.savefig(Path(wpath, f'images/particle_images/img_{i:04d}.jpg'), dpi=400)

os.system(f"gm convert -delay 10 -loop 0 {Path(wpath, 'images/particle_images', 'img_*.jpg')} {Path(wpath, 'images/particles.gif')}")