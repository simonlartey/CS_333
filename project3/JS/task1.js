/**
 * File: identifierRules.js
 * Author: Simon Lartey
 * Date: 10/19/2025
 * 
 * Description:
 * This program demonstrates the rules for identifier naming,
 * variable declarations, and scoping in JavaScript.
 * 
 * It serves as a simple tutorial for beginners learning how to 
 * create and use variables in JavaScript.
 */


/* =======================================================
   IDENTIFIER NAMING RULES
   ======================================================= */

/**
 * Identifiers can be used for variables, constants, functions,
 * classes, or object properties.
 * 
 * They must begin with a letter, underscore (_), or dollar sign ($),
 * and can include digits after the first character.
 * They are case-sensitive and cannot be JavaScript reserved words.
 */

let userName = "Simon";      // starts with a letter — valid
let _count = 5;              // starts with underscore — valid
let $price = 19.99;          // starts with dollar sign — valid
// let 2ndValue = 10;        // invalid — cannot start with a number
// let let = "wrong";        // invalid — reserved word

console.log(userName, _count, $price);


/* =======================================================
   RESERVED WORDS
   ======================================================= */

/**
 * JavaScript keywords like 'if', 'for', or 'let' cannot be
 * used as variable names.
 * 
 * However, they can be used as *property names* inside
 * objects or classes.
 */

let car = {
    if: "Tesla",
    else: "Ford",
    let: "Toyota"
};

console.log(car.if, car.let); // Works fine


/* =======================================================
   UNICODE CHARACTERS
   ======================================================= */

/**
 * JavaScript identifiers can include characters from the 
 * full Unicode set, not just English letters.
 * This means you can technically use non-English letters
 * in variable names.
 */
let ቍቐቖ = "Unicode allowed!";
console.log(ቍቐቖ);


/* =======================================================
   VALID STARTING CHARACTERS
   ======================================================= */

/**
 * Valid identifiers can start with:
 *   - a letter (A–Z, a–z)
 *   - an underscore (_)
 *   - a dollar sign ($)
 * 
 * Invalid examples are commented out below.
 */

let _total = 100;
let $tax = 0.07;
let userID = 12345;
// let #invalid = 10;    //  invalid symbol
// let %badName = true;  //  invalid symbol


/* =======================================================
   VARIABLE DECLARATIONS
   ======================================================= */

/**
 * JavaScript provides three ways to declare variables:
 *   1. var   → function-scoped (older style)
 *   2. let   → block-scoped (modern default)
 *   3. const → block-scoped constant (cannot be reassigned)
 */

var city = "Waterville";
let age = 21;
const college = "Colby";

console.log(city, age, college);


/* =======================================================
   SCOPE DEMONSTRATION
   ======================================================= */

/**
 * Scope determines where a variable can be accessed in a program.
 * 
 * JavaScript has three main types of scope:
 *   - Global Scope (accessible anywhere)
 *   - Function Scope (created with var)
 *   - Block Scope (created with let or const)
 */

var globalVar = "I am global!";

function scopeExample() {
    var funcVar = "I live inside this function.";

    if (true) {
        let blockVar = "I exist only in this block.";
        const blockConst = "I'm also block-scoped!";
        console.log(blockVar);     // works here
        console.log(blockConst);   // works here
    }

    console.log(funcVar);          // works
    // console.log(blockVar);      // ReferenceError
}

scopeExample();

console.log(globalVar);            //  works
// console.log(funcVar);           //  ReferenceError — function-scoped variable



