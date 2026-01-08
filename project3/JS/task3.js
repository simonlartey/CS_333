/**
 * File: task3.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 *
 * Description:
 * This program demonstrates JavaScript's type system — 
 * including primitive and aggregate types — and how operators 
 * like +, -, *, /, and % behave when applied to different data types.
 */

// =======================================================
// BOOLEAN
// =======================================================
console.log("=== Boolean Type ===");
const isAvailable = true;
const isDone = false;

console.log("isAvailable:", isAvailable);
console.log("isDone:", isDone);

const greaterCheck = 5 > 2;
const equalityCheck = 10 === 10.0;
console.log("5 > 2:", greaterCheck);
console.log("10 === 10.0:", equalityCheck);

// Boolean arithmetic
console.log("true + false =", true + false);   // 1
console.log("true * true =", true * true);     // 1
console.log("false / true =", false / true);   // 0
console.log("\n");


// =======================================================
// NULL
// =======================================================
console.log("=== Null Type ===");
const emptyValue = null;
console.log("emptyValue:", emptyValue);

console.log("null + 10 =", null + 10);   // 10
console.log("null * 3 =", null * 3);     // 0
console.log("null / null =", null / null); // NaN
console.log("\n");


// =======================================================
// UNDEFINED
// =======================================================
console.log("=== Undefined Type ===");
let userInput;
console.log("userInput:", userInput);

console.log("undefined + 5 =", undefined + 5);  // NaN
console.log("undefined * 2 =", undefined * 2);  // NaN
console.log("\n");


// =======================================================
// STRING
// =======================================================
console.log("=== String Type ===");
const firstName = "Joyce";
const lastName = "Larson";

console.log(`"${firstName}" + "${lastName}" =`, firstName + lastName); // concatenation
console.log(`"${firstName}" - "${lastName}" =`, firstName - lastName); // NaN
console.log(`"5" + 5 =`, "5" + 5); // "55"
console.log(`"5" - 5 =`, "5" - 5); // 0
console.log("\n");


// =======================================================
// NUMBER
// =======================================================
console.log("=== Number Type ===");
const numA = 17;
const numB = 0b1111;   // binary
const numC = 0xF;      // hexadecimal
const numD = 7.5;

console.log("numA:", numA, "| type:", typeof numA);
console.log("numB:", numB, "| type:", typeof numB);
console.log("numC:", numC, "| type:", typeof numC);
console.log("numD:", numD, "| type:", typeof numD);

console.log("17 + 5 =", 17 + 5);
console.log("17 / 4 =", 17 / 4);
console.log("17 % 4 =", 17 % 4);
console.log("1 / 0 =", 1 / 0);   // Infinity
console.log("-1 / 0 =", -1 / 0); // -Infinity
console.log("\n");


// =======================================================
// BIGINT
// =======================================================
console.log("=== BigInt Type ===");
const bigX = 5000000000000n;
const bigY = BigInt(250);
console.log("bigX + bigY =", bigX + bigY);
console.log("bigX * bigY =", bigX * bigY);
console.log("\n");


// =======================================================
// SYMBOL
// =======================================================
console.log("=== Symbol Type ===");
const symUser = Symbol("user");
const symAccount = Symbol("user"); // different even if same description
console.log("symUser === symAccount:", symUser === symAccount);

const symA = Symbol.for("session");
const symB = Symbol.for("session");
console.log("symA === symB:", symA === symB);

const uniqueId = Symbol("id");
const profile = { [uniqueId]: 12345, name: "Amira", level: "Junior" };
console.log("profile object:", profile);
console.log("\n");


// =======================================================
// OBJECTS AND CLASSES (Aggregate Types)
// =======================================================
console.log("=== Object & Class Types ===");

// Object literal
const petDog = {
    name: "Buddy",
    breed: "Golden Retriever",
    age: 4,
    bark() {
        console.log(`${this.name} barks loudly!`);
    }
};
petDog.bark();

// Function constructor
function Animal(type, sound) {
    this.type = type;
    this.sound = sound;
    this.makeSound = function() {
        console.log(`${this.type} makes ${this.sound} sound.`);
    };
}
const cat = new Animal("Cat", "meow");
cat.makeSound();

// Class syntax
class Vehicle {
    constructor(make, model, year) {
        this.make = make;
        this.model = model;
        this.year = year;
    }

    describe() {
        console.log(`This is a ${this.year} ${this.make} ${this.model}.`);
    }
}
const myCar = new Vehicle("Tesla", "Model 3", 2023);
myCar.describe();
console.log("\n");


// =======================================================
// ARRAYS AND TYPEOF BEHAVIOR
// =======================================================
console.log("=== Array Type ===");
const fruits = ["apple", "banana", "cherry", 5];
console.log("fruits:", fruits);
console.log("typeof fruits:", typeof fruits);
