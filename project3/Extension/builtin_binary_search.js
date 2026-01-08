/*
 * File: builtin_binary_search.js
 * Author: Simon Lartey
 * Date: 10/22/2025
 *
 * Description:
 * This program demonstrates how JavaScript’s built-in array methods
 * can perform efficient searching operations similar to binary search.
 * 
 * It compares:
 *  1. Linear search using `indexOf()` and `findIndex()`
 *  2. Efficient searching in sorted data using `Array.prototype.binarySearch()` (in modern runtimes)
 *  3. Manual binary search for comparison
 * 
 * The goal is to show how higher-level abstractions hide algorithmic details
 * while improving readability and reducing error-prone code.
 */

// ================================================
// 1️⃣  Using indexOf() – basic linear search
// ================================================
const numbers = [10, 20, 30, 40, 50, 60, 70];
const target = 50;

const index1 = numbers.indexOf(target);

console.log("Using indexOf():");
console.log(index1 === -1
    ? `The value ${target} was not found.`
    : `The value ${target} was found at index ${index1}.`);
console.log();


// ================================================
// 2️⃣  Using findIndex() – callback-based search
// ================================================
const index2 = numbers.findIndex(num => num === target);

console.log("Using findIndex():");
console.log(index2 === -1
    ? `The value ${target} was not found.`
    : `The value ${target} was found at index ${index2}.`);
console.log();


// ================================================
// 3️⃣  Manual binary search for comparison
// ================================================
function binarySearch(arr, value) {
    let left = 0;
    let right = arr.length - 1;

    while (left <= right) {
        const mid = Math.floor((left + right) / 2);

        if (arr[mid] === value) return mid;
        if (arr[mid] < value) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

const index3 = binarySearch(numbers, target);

console.log("Using manual binary search:");
console.log(index3 === -1
    ? `The value ${target} was not found.`
    : `The value ${target} was found at index ${index3}.`);
console.log();


// ================================================
// 4️⃣  Using the proposed built-in Array.prototype.binarySearch()
//     (Currently available in V8 runtimes like Node.js 22+)
// ================================================

if (typeof numbers.binarySearch === "function") {
    const index4 = numbers.binarySearch(target);
    console.log("Using built-in binarySearch() (Node.js 22+):");
    console.log(index4 === -1
        ? `The value ${target} was not found.`
        : `The value ${target} was found at index ${index4}.`);
} else {
    console.log("⚠️ Your runtime does not yet support Array.prototype.binarySearch().");
}
