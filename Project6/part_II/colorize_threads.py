import sys
import threading
import time
from PIL import Image

# Pixel operator (same as C version)
def transform_pixel(r, g, b):
    r2 = (220 + r)//2 if r > 128 else (30 + r)//2
    g2 = (220 + g)//2 if g > 128 else (30 + g)//2
    b2 = (220 + b)//2 if b > 128 else (30 + b)//2
    return (r2, g2, b2)

# Worker thread
def worker(pixelmap, width, height, start_row, end_row):
    for y in range(start_row, end_row):
        for x in range(width):
            r, g, b = pixelmap[x, y]
            pixelmap[x, y] = transform_pixel(r, g, b)

def run_threads(filename, num_threads):
    img = Image.open(filename).convert("RGB")
    pixelmap = img.load()

    width, height = img.size
    rows_per_thread = height // num_threads

    threads = []
    t_start = time.time()

    for i in range(num_threads):
        start_row = i * rows_per_thread
        end_row = height if i == num_threads - 1 else (i + 1) * rows_per_thread

        t = threading.Thread(target=worker, args=(pixelmap, width, height, start_row, end_row))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    t_end = time.time()

    out_name = f"bold_{num_threads}thread.ppm"
    img.save(out_name)

    print(f"{num_threads} threads time: {t_end - t_start:.6f} sec (output: {out_name})")
    return t_end - t_start

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 colorize_threads.py input.ppm")
        return

    filename = sys.argv[1]

    print("Running serial (1 thread)...")
    run_threads(filename, 1)

    print("Running 2 threads...")
    run_threads(filename, 2)

    print("Running 4 threads...")
    run_threads(filename, 4)

if __name__ == "__main__":
    main()
