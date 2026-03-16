import matplotlib.pyplot as plt

threads = [1, 2, 4]
avg_times = [0.923051, 0.959414, 0.984903] 

plt.figure(figsize=(10,6))
plt.plot(threads, avg_times, marker='o', linewidth=2)

plt.title("Task 2: Runtime vs Number of Threads (Python)")
plt.xlabel("Number of Threads")
plt.ylabel("Average Runtime (seconds)")
plt.grid(True, linestyle='--', alpha=0.6)

plt.xticks(threads, ["1 Thread", "2 Threads", "4 Threads"])

plt.tight_layout()
plt.savefig("task2_runtime_graph.png", dpi=200)
plt.show()
