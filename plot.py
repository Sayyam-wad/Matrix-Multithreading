import matplotlib.pyplot as plt

threads = []
times = []

with open("results.txt") as f:
    next(f)
    for line in f:
        t, time = line.split()
        threads.append(int(t))
        times.append(float(time))

plt.plot(threads, times, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (sec)")
plt.title("Multithreading Performance Analysis")
plt.grid()

plt.savefig("graph.png")
plt.show()