/**
 * @file   LinkedList.js
 * @brief  Implementation of a polymorphic LinkedList data structure in JavaScript.
 * @author Simon Lartey
 * @date   10/29/2025
 *
 * @description
 * This program demonstrates how a LinkedList can be implemented in JavaScript
 * using classes and polymorphism. The LinkedList stores generic data using nodes,
 * similar to how pointers and function handlers work in C. It also includes all
 * major operations: push, pop, append, remove, find, size, clear, and map.
 */

/** Class representing a single Node. */
class Node {
    /**
     * Creates a Node instance.
     * @param {*} data - The data stored in the node.
     */
    constructor(data) {
      this.data = data;
      this.next = null;
    }
  }
  
  /** Class representing a generic LinkedList. */
  class LinkedList {
    constructor() {
      this.head = null;
    }
  
    /** Add a new node to the front of the list. */
    push(data) {
      const newNode = new Node(data);
      newNode.next = this.head;
      this.head = newNode;
    }
  
    /** Remove and return the data from the front node. */
    pop() {
      if (!this.head) return null;
      const value = this.head.data;
      this.head = this.head.next;
      return value;
    }
  
    /** Add a new node to the end of the list. */
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
  
    /**
     * Remove the first node matching target based on a comparison function.
     * @param {*} target - The value to remove.
     * @param {Function} compFunc - Comparison function: returns true if match found.
     */
    remove(target, compFunc) {
      if (!this.head) return null;
  
      if (compFunc(this.head.data, target)) {
        const value = this.head.data;
        this.head = this.head.next;
        return value;
      }
  
      let current = this.head;
      while (current.next) {
        if (compFunc(current.next.data, target)) {
          const value = current.next.data;
          current.next = current.next.next;
          return value;
        }
        current = current.next;
      }
      return null;
    }
  
    /**
     * Find a node matching target using comparison function.
     * @param {*} target - The value to search for.
     * @param {Function} compFunc - Comparison function for equality.
     */
    find(target, compFunc) {
      let current = this.head;
      while (current) {
        if (compFunc(current.data, target)) return current.data;
        current = current.next;
      }
      return null;
    }
  
    /** Return the number of nodes in the list. */
    size() {
      let count = 0;
      let current = this.head;
      while (current) {
        count++;
        current = current.next;
      }
      return count;
    }
  
    /**
     * Remove all nodes, optionally freeing associated resources.
     * @param {Function} freeFunc - Optional cleanup function for node data.
     */
    clear(freeFunc) {
      let current = this.head;
      while (current) {
        if (freeFunc) freeFunc(current.data);
        current = current.next;
      }
      this.head = null;
    }
  
    /**
     * Apply a function to each node’s data.
     * @param {Function} mapFunc - Function to apply to each node.
     */
    map(mapFunc) {
      let current = this.head;
      while (current) {
        mapFunc(current.data);
        current = current.next;
      }
    }
  }
  
  module.exports = { LinkedList };
  