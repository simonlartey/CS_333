/**
 * File: task2.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 *
 * Description:
 * This program demonstrates how to implement a Binary Search algorithm in JavaScript.
 * It uses functions, loops, and conditional statements to find a target value in a
 * sorted array. The program also serves as an example of JavaScript syntax—showing
 * how to declare variables, define functions, and use control flow.
 */

/**
 * Performs a binary search on a sorted array to find the index of a target value.
 *
 * @param {number[]} arr - The sorted array to search.
 * @param {number} target - The value to look for.
 * @returns {number} The index of the target if found, or -1 if not found.
 */
function binarySearch(arr, target) {
    let left = 0;
    let right = arr.length - 1;

    // Continue while there is still a range to search
    while (left <= right) {
        // Find the midpoint of the current range
        const mid = Math.floor((left + right) / 2);

        // Check the value at the midpoint
        if (arr[mid] === target) {
            return mid; // Target found
        }

        // If target is smaller, ignore the right half
        if (arr[mid] > target) {
            right = mid - 1;
        } 
        // Otherwise, ignore the left half
        else {
            left = mid + 1;
        }
    }

    // Target not found
    return -1;
}


/* =======================================================
   Example 1: Target value is present in the array
   ======================================================= */

const numbers1 = [51, 17, 15, 24, 72, 17, 69, 31, 62, 100];
numbers1.sort((a, b) => a - b);
const target1 = 69;

console.log("Array 1:", numbers1);

const result1 = binarySearch(numbers1, target1);

if (result1 === -1) {
    console.log(`The target ${target1} was not found in the array.\n`);
} else {
    console.log(`The target ${target1} was found at index ${result1}.\n`);
}


/* =======================================================
   Example 2: Target value is NOT present in the array
   ======================================================= */

const numbers2 = [51, 17, 15, 24, 72, 17, 69, 31, 62, 100];
numbers2.sort((a, b) => a - b);
const target2 = 99;

console.log("Array 2:", numbers2);

const result2 = binarySearch(numbers2, target2);

if (result2 === -1) {
    console.log(`The target ${target2} was not found in the array.`);
} else {
    console.log(`The target ${target2} was found at index ${result2}.`);
}
