/*
 * Author: Simon Lartey
 * Date: 10/29/2025
 * Project: CS333 Project 04 - Extension
 * Description:
 *   Demonstrates two methods for creating a generic LinkedList in JavaScript:
 *   (1) Class-based implementation (OOP style)
 *   (2) Factory function implementation (Functional style)
 *
 * How to run:
 *   node genericListExtension.js
 */

/* ============================
 * METHOD 1: CLASS-BASED LIST
 * ============================
 */

class Node {
    constructor(data) {
      this.data = data;
      this.next = null;
    }
  }
  
  class LinkedList {
    constructor() {
      this.head = null;
    }
  
    append(data) {
      const newNode = new Node(data);
      if (!this.head) {
        this.head = newNode;
        return;
      }
      let current = this.head;
      while (current.next) current = current.next;
      current.next = newNode;
    }
  
    map(callback) {
      let current = this.head;
      while (current) {
        callback(current.data);
        current = current.next;
      }
    }
  
    clear() {
      this.head = null;
    }
  }
  
  /* ================================
   * METHOD 2: FUNCTIONAL LINKEDLIST
   * ================================
   */
  
  function createLinkedList() {
    let head = null;
  
    function append(data) {
      const newNode = { data, next: null };
      if (!head) {
        head = newNode;
        return;
      }
      let current = head;
      while (current.next) current = current.next;
      current.next = newNode;
    }
  
    function map(callback) {
      let current = head;
      while (current) {
        callback(current.data);
        current = current.next;
      }
    }
  
    function clear() {
      head = null;
    }
  
    return { append, map, clear };
  }
  
  /* =====================
   * TESTING BOTH METHODS
   * =====================
   */
  
  console.log("=== Testing Method 1: Class-Based LinkedList ===");
  const numList = new LinkedList();
  numList.append(10);
  numList.append(20);
  numList.append(30);
  numList.append(40);
  
  console.log("Numbers:");
  numList.map((x) => console.log(x));
  
  const strList = new LinkedList();
  strList.append("Tokyo");
  strList.append("Nairobi");
  strList.append("Oslo");
  console.log("\nStrings:");
  strList.map((x) => console.log(x));
  
  
  console.log("\n=== Testing Method 2: Functional LinkedList ===");
  const mixedList = createLinkedList();
  mixedList.append(42);
  mixedList.append("Cairo");
  mixedList.append({ city: "Lisbon", country: "Portugal" });
  
  console.log("Mixed data types:");
  mixedList.map((item) => console.log(item));
  