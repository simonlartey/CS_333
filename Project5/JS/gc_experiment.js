/*
 * File: gc_experiment.js
 * Author: Simon Lartey
 * Description:
 *     This program repeatedly allocates large arrays to create memory pressure
 *     and measure JavaScript garbage-collection timing spikes.
 *
 * How to Run:
 *     node --expose-gc gc_experiment.js
 */

function allocateMemory() {
    // Create a large array every time the function is called
    let arr = new Array(500000).fill(1);
}

function runExperiment(iterations) {
    const times = [];

    for (let i = 0; i < iterations; i++) {

        const start = performance.now();

        // Allocate multiple large arrays per iteration
        allocateMemory();
        allocateMemory();
        allocateMemory();

        const end = performance.now();
        const duration = end - start;
        times.push(duration);

        console.log(`Call ${i}: ${duration.toFixed(3)} ms`);

        // Detect probable GC spikes
        if (duration > 5) {
            console.log(`GC detected at call ${i} (took ${duration.toFixed(3)} ms)`);
        }
    }

    return times;
}

runExperiment(3000);
