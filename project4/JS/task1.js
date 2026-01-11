/*
 * Author: Simon Lartey
 * Date: 10/29/2025
 * Project: CS333 Project 04 – Part II: Semantics of Selected Languages
 * Description: 
 * This program implements a polymorphic Bubble Sort algorithm in JavaScript capable of sorting
 * arrays of any data type in any desired order. It accepts a user-defined comparison function,
 * enabling custom sorting semantics similar to function pointers in C. The demonstration includes
 * sorting both numerical and string data types in ascending, descending, and alphabetical order.
 * 
 * How to run:
 * node task1.js
 */

 /**
  * Sorts the given array according to a provided comparison function.
  *
  * @param {Array} arr - The array to be sorted.
  * @param {Function} comparisonFunction - Function that compares two elements and determines order.
  *                                        It should return 1 if the first element should come after the second,
  *                                        -1 if it should come before, and 0 if they are equal.
  */
function bubbleSort(arr, comparisonFunction) {
    for (let i = 0; i < arr.length; i++) {
        let hasSwapped = false;
        for (let j = 0; j < arr.length - i - 1; j++) {
            if (comparisonFunction(arr[j], arr[j + 1]) === 1) {
                const temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                hasSwapped = true;
            }
        }
        if (!hasSwapped) break; // Optimization: stop if already sorted
    }
}

/**
 * Comparison function for sorting numbers in ascending order.
 *
 * @param {number} a - The first number.
 * @param {number} b - The second number.
 * @returns {number} Returns 1 if `a > b`, -1 if `a < b`, and 0 if equal.
 */
function compareNumbersAscending(a, b) {
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

/**
 * Comparison function for sorting numbers in descending order.
 *
 * @param {number} a - The first number.
 * @param {number} b - The second number.
 * @returns {number} Returns 1 if `a < b`, -1 if `a > b`, and 0 if equal.
 */
function compareNumbersDescending(a, b) {
    if (a < b) return 1;
    else if (a > b) return -1;
    else return 0;
}

/**
 * Comparison function for sorting strings alphabetically (A–Z).
 *
 * @param {string} a - The first string.
 * @param {string} b - The second string.
 * @returns {number} Returns 1 if `a` should come after `b`, -1 if before, and 0 if equal.
 */
function compareStringsAlphabetical(a, b) {
    a = a.toLowerCase();
    b = b.toLowerCase();
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

/**
 * Comparison function for sorting strings in reverse alphabetical order (Z–A).
 *
 * @param {string} a - The first string.
 * @param {string} b - The second string.
 * @returns {number} Returns 1 if `a` should come before `b`, -1 if after, and 0 if equal.
 */
function compareStringsReverse(a, b) {
    a = a.toLowerCase();
    b = b.toLowerCase();
    if (a < b) return 1;
    else if (a > b) return -1;
    else return 0;
}

/**
 * Main driver function demonstrating polymorphic sorting
 * with both numbers and strings.
 */
function main() {
    console.log("=== Testing Bubble Sort with Numbers ===");
    const numbers = [42, 15, 8, 23, 4, 16, 108];
    console.log("Original:", numbers.slice());

    bubbleSort(numbers, compareNumbersAscending);
    console.log("Ascending:", numbers);

    bubbleSort(numbers, compareNumbersDescending);
    console.log("Descending:", numbers);

    console.log("\n=== Testing Bubble Sort with Strings ===");
    const cities = ["Tokyo", "Nairobi", "Cairo", "Lisbon", "Oslo"];
    console.log("Original:", cities.slice());

    bubbleSort(cities, compareStringsAlphabetical);
    console.log("Alphabetical:", cities);

    bubbleSort(cities, compareStringsReverse);
    console.log("Reverse Alphabetical:", cities);
}

// Run main
main();
