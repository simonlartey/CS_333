/**
 * @file   testLinkedList.js
 * @brief  Test program for LinkedList class using multiple data types.
 * @author Simon Lartey
 * @date   10/29/2025
 * How to run: node testLinkedList.js
 */

const { LinkedList } = require("./LinkedList");

/* Comparison helpers */
const compareNumbers = (a, b) => a === b;
const compareStrings = (a, b) => a.toLowerCase() === b.toLowerCase();

/* Print functions */
const print = (data) => console.log("value:", data);

function main() {
  console.log("=== Testing LinkedList with Numbers ===");
  const numList = new LinkedList();

  for (let i = 0; i < 10; i += 2) numList.push(i);
  numList.map(print);

  numList.append(20);
  console.log("\nAfter append:");
  numList.map(print);

  numList.remove(4, compareNumbers);
  console.log("\nAfter removing 4:");
  numList.map(print);

  console.log("\nList size:", numList.size());

  numList.clear();
  console.log("\nAfter clear:");
  numList.map(print);

  console.log("\n=== Testing LinkedList with Strings ===");
  const strList = new LinkedList();
  ["Tokyo", "Nairobi", "Oslo", "Lisbon", "Cairo"].forEach((s) => strList.append(s));

  strList.map(print);

  strList.push("New York");
  console.log("\nAfter push:");
  strList.map(print);

  const removed = strList.pop();
  console.log("\nPopped:", removed);

  console.log("\nAfter pop:");
  strList.map(print);

  strList.remove("Oslo", compareStrings);
  console.log("\nAfter removing 'Oslo':");
  strList.map(print);

  console.log("\nList size:", strList.size());
}

main();
