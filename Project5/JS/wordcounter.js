const fs = require("fs");

// normalize a word: lowercase + strip punctuation
function normalize(word) {
    return word
        .toLowerCase()
        .replace(/^[^\w]+|[^\w]+$/g, "");  // remove punctuation at start/end
}

function countWords(filename) {
    const text = fs.readFileSync(filename, "utf8");

    const words = text.split(/\s+/);
    const counts = new Map();

    for (let raw of words) {
        const word = normalize(raw);
        if (word.length === 0) continue;

        counts.set(word, (counts.get(word) || 0) + 1);
    }

    // convert to array and sort by frequency
    const sorted = [...counts.entries()]
        .sort((a, b) => b[1] - a[1])
        .slice(0, 20);

    console.log("=== Top 20 Most Frequent Words ===");
    for (let [word, count] of sorted) {
        console.log(`${word}: ${count}`);
    }
}

if (process.argv.length < 3) {
    console.error("Usage: node wordcounter.js <filename>");
    process.exit(1);
}

countWords(process.argv[2]);
