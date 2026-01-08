/**
 * File: compare_js.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 *
 * Description:
 * JavaScript version of code demonstrating syntax, scoping, and function behavior.
 * Mirrors the Python example for explicit comparison.
 */

// ---------------------------
// 1️⃣ Variable Declaration
// ---------------------------
let x = 42;
let y = "hello";
let z = [1, 2, 3];

console.log("JavaScript Variable Types:");
console.log("x =", x, "type:", typeof x);
console.log("y =", y, "type:", typeof y);
console.log("z =", z, "type:", typeof z);
console.log("\n");


// ---------------------------
// 2️⃣ Scoping Rules (block + lexical)
// ---------------------------
let globalVar = "global";

function outerFunction() {
    let outerVar = "outer";
    
    function innerFunction() {
        let innerVar = "inner";
        console.log(`Accessing ${globalVar} from global scope`);
        console.log(`Accessing ${outerVar} from enclosing scope`);
        console.log(`Accessing ${innerVar} from local scope`);
    }

    innerFunction();
}

outerFunction();
console.log("\n");


// ---------------------------
// 3️⃣ Control Flow
// ---------------------------
let n = 5;
if (n > 10) {
    console.log("n is greater than 10");
} else if (n === 5) {
    console.log("n is exactly 5");
} else {
    console.log("n is less than 10");
}
console.log();

for (let i = 0; i < 3; i++) {
    console.log(`for loop count: ${i}`);
}
console.log();

while (n > 0) {
    console.log(`while loop count: ${n}`);
    n--;
}
console.log();


// ---------------------------
// 4️⃣ Function as First-Class Object
// ---------------------------
function greet(name) {
    return `Hello, ${name}!`;
}

// Assign function to variable
const welcome = greet;
console.log(welcome("Simon"));

// Pass function as argument
function execute(func, arg) {
    console.log("Executing passed function...");
    console.log(func(arg));
}

execute(greet, "Joyce");

// Return function from function
function multiplier(factor) {
    return function(n) {
        return n * factor;
    };
}

const double = multiplier(2);
console.log("Double of 10 is:", double(10));
console.log();


// ---------------------------
// 5️⃣ Built-in Types and Operators
// ---------------------------
let a = 10, b = 3;
console.log(`Addition: ${a + b}`);
console.log(`Subtraction: ${a - b}`);
console.log(`Multiplication: ${a * b}`);
console.log(`Division: ${a / b}`);
console.log(`Modulus: ${a % b}`);
console.log(`Exponentiation: ${a ** b}`);
console.log();
