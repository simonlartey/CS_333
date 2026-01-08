/**
 * File: task5.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 *
 * Description:
 * Demonstrates how JavaScript treats functions as data types.
 * Functions can be assigned to variables, passed as arguments,
 * returned from other functions, and executed through references.
 * Also shows arrow (anonymous) functions and closures.
 */

// =======================================================
// 1. Assigning a function to a variable
// =======================================================

// Function expression assigned to a variable
const greetFunction = function sayHello() {
    console.log("Hey there! Welcome to the demo.");
};

// Calling the function using the variable reference
greetFunction();
console.log();


// =======================================================
// 2. Passing a function as an argument to another function
// =======================================================

// Function that will be passed as an argument
function makeIntroduction(name) {
    return `Nice to meet you, ${name}!`;
}

// Higher-order function with a function parameter
function displayIntroduction(name, country, introFunc) {
    console.log(introFunc(name));
    console.log(`You are visiting from ${country}.`);
}

// Passing the function as an argument
displayIntroduction("Kwame Mensah", "Ghana", makeIntroduction);
console.log();


// =======================================================
// 3. Returning a function from another function
// =======================================================

function chooseMathOperation(choice) {
    switch (choice) {
        case 1:
            return function add(a, b) {
                return a + b;
            };
        case 2:
            return function subtract(a, b) {
                return a - b;
            };
        case 3:
            return function multiply(a, b) {
                return a * b;
            };
        case 4:
            return function divide(a, b) {
                return a / b;
            };
        default:
            console.log("Invalid option! Please enter a number between 1 and 4.");
    }
}

// Getting returned functions and executing them
const adder = chooseMathOperation(1);
console.log(`6 + 9 = ${adder(6, 9)}`);

const divider = chooseMathOperation(4);
console.log(`20 / 5 = ${divider(20, 5)}`);
console.log();


// =======================================================
// 4. Anonymous & Arrow Functions
// =======================================================

// Arrow function (anonymous) assigned to a variable
const welcomeUser = (name) => `Hello, ${name}! Have a great day ahead!`;
console.log(welcomeUser("Ama"));  // Output: Hello, Ama! Have a great day ahead!

// Passing an anonymous arrow function as an argument
function executeBinaryOperation(operation, x, y) {
    console.log(`The output of this operation is ${operation(x, y)}.`);
}

// Passing an inline anonymous arrow function
executeBinaryOperation((x, y) => x - y, 15, 4);  // Output: The output of this operation is 11.
console.log();


// =======================================================
// 5. Returning an anonymous function (demonstrating closures)
// =======================================================

function createExponentFunction(power) {
    return (number) => number ** power;
}

const squareNum = createExponentFunction(2);
const quadrupleNum = createExponentFunction(4);

console.log(`Square of 8 = ${squareNum(8)}`);       // Output: 64
console.log(`8 raised to the 4th power = ${quadrupleNum(8)}`); // Output: 4096
