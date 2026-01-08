/*
 * File: task4.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 *
 * Description:
 * Demonstrates JavaScript control flow statements including conditionals,
 * loops, branching, switch, ternary, and error handling.
 * Each example includes comments for clarity.
 */

// =======================================================
// CONDITIONAL STATEMENTS: if, else, else if
// =======================================================
let temperature = 33;

if (temperature > 30)
    console.log("It's a hot day!");

if (temperature >= 20 && temperature <= 30) {
    console.log("The temperature is moderate.");
    console.log(`Current temperature: ${temperature}°C`);
}

if (temperature < 10) {
    console.log("It's very cold!");
}
console.log("\n");

// if...else
let city = "Paris";

if (city === "Paris") {
    console.log("You are in France.");
} else {
    console.log("You are somewhere else.");
}

city = "Accra";
if (city === "Paris") {
    console.log("You are in France.");
} else {
    console.log("You are in Ghana.");
}
console.log("\n");

// if...else if...else
let grade = "B";

if (grade === "A") {
    console.log("Excellent!");
} else if (grade === "B") {
    console.log("Good job!");
} else if (grade === "C") {
    console.log("Satisfactory.");
} else {
    console.log("Needs improvement.");
}
console.log("\n");

// =======================================================
// LOOPS: while, do...while, for, for...in, for...of
// =======================================================
let count = 0;
while (count < 3) {
    console.log(`while loop count: ${count}`);
    count++;
}
console.log("\n");

let index = 0;
do {
    console.log(`do...while index: ${index}`);
    index++;
} while (index < 2);
console.log("\n");

for (let i = 1; i <= 4; i++) {
    console.log(`for loop iteration: ${i}`);
}
console.log("\n");

const planets = {1: "Mercury", 2: "Venus", 3: "Earth", 4: "Mars"};
for (let key in planets) {
    console.log(`for...in → Planet ${key}: ${planets[key]}`);
}
console.log("\n");

const fruits = ["apple", "banana", "cherry"];
for (let fruit of fruits) {
    console.log(`for...of fruit: ${fruit}`);
}
console.log("\n");

// =======================================================
// BRANCHING: break and continue
// =======================================================
for (let n = 0; n < 8; n++) {
    if (n === 4) {
        console.log("break triggered at n = 4!");
        break;
    }
    console.log(`n = ${n}`);
}
console.log("\n");

for (let n = 0; n < 8; n++) {
    if (n % 3 === 0) continue;
    console.log(`continue example: n = ${n}`);
}
console.log("\n");

// =======================================================
// SWITCH STATEMENT
// =======================================================
let weekday = 5;
switch (weekday) {
    case 0:
        console.log("It's Sunday.");
        break;
    case 1:
        console.log("It's Monday.");
        break;
    case 2:
        console.log("It's Tuesday.");
        break;
    case 3:
        console.log("It's Wednesday.");
        break;
    case 4:
        console.log("It's Thursday.");
        break;
    case 5:
        console.log("It's Friday!");
        break;
    case 6:
        console.log("It's Saturday.");
        break;
    default:
        console.log("Invalid day entered.");
}
console.log("\n");

// =======================================================
// TERNARY OPERATOR
// =======================================================
let mood = (temperature > 25) ? "happy" : "chilly";
console.log(`Mood based on weather: ${mood}`);

mood = (temperature < 0) ? "freezing" : "comfortable";
console.log(`Temperature check: ${mood}`);
console.log("\n");

// =======================================================
// RETURN STATEMENT
// =======================================================
function calculateSquare(num) {
    if (num < 0) {
        console.log("Negative number detected. Returning early...");
        return;
    }
    return num * num;
}

console.log(`Square of 5: ${calculateSquare(5)}`);
calculateSquare(-3);
console.log("\n");

// =======================================================
// ERROR HANDLING: try...catch...finally
// =======================================================
try {
    console.log("Trying to parse JSON...");
    const data = JSON.parse('{"name": "Simon"}');
    console.log("Parsing successful:", data);
} catch (error) {
    console.log("Error during JSON parsing:", error.message);
} finally {
    console.log("Finished JSON operation.\n");
}

try {
    console.log("Attempting division...");
    const result = 10 / 0;
    if (!isFinite(result)) throw new Error("Division by zero!");
    console.log(result);
} catch (error) {
    console.log("Caught error:", error.message);
} finally {
    console.log("Division attempt complete.");
}
