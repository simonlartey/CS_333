/* detect_garbage.c
 * Author: Simon Lartey
 * Date: 11/13/25
 * Identify garbage heap chunks using the mark-and-sweep method
 * 
 * How to compile:
 *     gcc detect_garbage.c -o detect_garbage
 *
 * How to run:
 *     ./detect_garbage
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10
#define MAX_HEAP_SIZE 10

// A chunk on the heap could refer to other chunks on the heap
// the "marked" field is for use by the mark and sweep algorithm and
// isn't part of the data the code accesses.
typedef struct _HeapChunk {
    int num_references;
    int marked;
    struct _HeapChunk **references;
} HeapChunk;

// Var on stack. Can have value that is a reference to the Heap, or it could
// have a different value.
// We indicate its value is on heap by having reference by non-null
typedef struct {
    char *name;
    HeapChunk *reference;
} Var;

// Program state has stack and heap separately both stored as array for
// simplicity
typedef struct {
    Var *stack;  // array of all current variables
    int num_vars_on_stack;

    // array of all allocated HeapChunks (so array of pointers)
    HeapChunk **heap;
    int num_heap_chunks;
} ProgramState;

// make a new program state
ProgramState *createProgramState() {
    ProgramState *state = (ProgramState *)malloc(sizeof(ProgramState));
    state->stack = (Var *)malloc(sizeof(Var) * MAX_STACK_SIZE);
    state->heap = (HeapChunk **)malloc(sizeof(HeapChunk *) * MAX_HEAP_SIZE);
    state->num_heap_chunks = 0;
    state->num_vars_on_stack = 0;
    return state;
}

// allocate a chunk and return the address to it,
// but also add it to our list of allocated chunks on heap
HeapChunk *HeapMalloc(ProgramState *state) {
    HeapChunk *chunk = (HeapChunk *)malloc(sizeof(HeapChunk));
    chunk->num_references = 0;
    chunk->references = NULL;
    state->heap[state->num_heap_chunks] = chunk;
    state->num_heap_chunks++;
    return chunk;
}

// update the stack (either add name/value pair or update value)
void setVar(ProgramState *state, char *var_name, HeapChunk *chunk) {
    int found = 0;
    for (int i = 0; i < state->num_vars_on_stack; i++) {
        if (strcmp(state->stack[i].name, var_name) == 0) {
            found = 1;
            state->stack[i].reference = chunk;
        }
    }
    if (!found) {
        state->stack[state->num_vars_on_stack].name = strdup(var_name);
        state->stack[state->num_vars_on_stack].reference = chunk;
        state->num_vars_on_stack++;
    }
}

// adds a reference from chunk_source to chunk_target.
// method is humorously badly written, don't try to do this for too many
// references.
void addReference(HeapChunk *chunk_source, HeapChunk *chunk_target) {
    if (chunk_source->num_references++ == 0)
        chunk_source->references = malloc(sizeof(HeapChunk *));
    else
        chunk_source->references =
            realloc(chunk_source->references,
                       chunk_source->num_references * sizeof(HeapChunk *));
    chunk_source->references[chunk_source->num_references - 1] = chunk_target;
}

// Mark and Sweep, but don't really sweep - just report which chunks are garbage.
// First, you should unmark all the heap chunks by setting the mark value to 0. 
// You need to use the heap chunk array to access all heap chunks
// Then, you should trace through all heap chunks you can find from the stack.
// You need to use the stack and then implement a depth first search that follows
// all references (even from HeapChunk to HeapChunk).  Be sure not to get
// caught in any circular references (i.e. think about your stopping conditions).
// Finally, you should loop through the heap array again, this time reporting for each
// HeapChunk whether it is reachable or garbage.
void dfsMark(HeapChunk *chunk) {
    if (chunk == NULL) return;

    if (chunk->marked == 1) return;   // already visited

    chunk->marked = 1;

    for (int i = 0; i < chunk->num_references; i++) {
        dfsMark(chunk->references[i]);
    }
}

void markAndSweep(ProgramState *state) {

    printf("\n=== Mark and Sweep Results ===\n");

    // 1. Unmark all heap chunks
    for (int i = 0; i < state->num_heap_chunks; i++) {
        state->heap[i]->marked = 0;
    }

    // 2. Mark reachable chunks via DFS starting from stack
    for (int i = 0; i < state->num_vars_on_stack; i++) {
        dfsMark(state->stack[i].reference);
    }

    // 3. Sweep: report status
    for (int i = 0; i < state->num_heap_chunks; i++) {
        HeapChunk *chunk = state->heap[i];
        printf("HeapChunk %d: %s\n",
               i,
               chunk->marked ? "REACHABLE" : "GARBAGE");
    }
}



int main() {
    ProgramState *state = createProgramState();

    // Stack variables (reachable root set)
    HeapChunk *a = HeapMalloc(state);
    setVar(state, "a", a);

    HeapChunk *b = HeapMalloc(state);
    setVar(state, "b", b);

    HeapChunk *c = HeapMalloc(state);
    setVar(state, "c", c);

    // Create a 3-chunk cycle unreachable from the stack
    HeapChunk *x = HeapMalloc(state);
    HeapChunk *y = HeapMalloc(state);
    HeapChunk *z = HeapMalloc(state);

    addReference(x, y);   // x -> y
    addReference(y, z);   // y -> z
    addReference(z, x);   // z -> x (cycle)

    // Run garbage collector
    markAndSweep(state);

    return 0;
}
