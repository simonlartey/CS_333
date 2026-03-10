import matplotlib.pyplot as plt

# === average values ===
serial_avg     = 0.557640  
one_thread_avg = 0.588422
two_thread_avg = 0.314563 
four_thread_avg = 0.257326 

# Data for plotting
threads = [0, 1, 2, 4]  
times = [serial_avg, one_thread_avg, two_thread_avg, four_thread_avg]

# Labels
thread_labels = ["Serial", "1 Thread", "2 Threads", "4 Threads"]

plt.figure(figsize=(8,5))
plt.plot(threads, times, marker="o", linewidth=2)


plt.xticks(threads, thread_labels)
plt.xlabel("Number of Threads")
plt.ylabel("Average Runtime (seconds)")
plt.title("Runtime vs Thread Count for Colorization Program")
plt.grid(True)

# Save figure
plt.savefig("runtime_plot.png", dpi=200)
print("Saved graph as runtime_plot.png")

plt.show()
