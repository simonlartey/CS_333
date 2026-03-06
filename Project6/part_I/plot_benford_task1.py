import matplotlib.pyplot as plt

# Version labels
versions = ["V1", "V2", "V3", "V4", "V5", "V6"]

# Average times (middle 3 runs)
avg_times = [
    0.001788,  
    0.001557,  
    0.004024,  
    0.001057,  
    0.001737,  
    0.001002   
]

plt.figure(figsize=(10, 6))
plt.plot(versions, avg_times, marker='o', linestyle='-', linewidth=2, markersize=8)

plt.title("Benford Task 1: Runtime vs Version", fontsize=16)
plt.xlabel("Version", fontsize=14)
plt.ylabel("Average Runtime (seconds)", fontsize=14)

plt.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.savefig("benford_task1_graph.png", dpi=200)
plt.show()
