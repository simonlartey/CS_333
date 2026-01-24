import pandas as pd
import matplotlib.pyplot as plt

# Load the results file
df = pd.read_table("malloc_results.txt", sep=" ")

# Renamed columns for clarity
df.columns = ["bytes", "avg_time_microseconds"]

# Convert bytes to MB for a nicer X-axis
df["MB"] = df["bytes"] / (1024 * 1024)

# Create the plot
plt.figure(figsize=(8, 5))
plt.plot(df["MB"], df["avg_time_microseconds"], marker='o')

# Labels and title
plt.xlabel("Allocated Memory (MB)")
plt.ylabel("Avg malloc() Time (microseconds)")
plt.title("Memory Allocation Time vs Allocation Size")

# Grid lines for readability
plt.grid(True)

# Show the graph
plt.show()
