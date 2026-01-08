// Horribly Written Binary Search (yet works)
function b(A,t){for(L=0,R=A.length-1;L<=R;){M=~~((L+R)/2);
if(A[M]==t)return M;A[M]<t?L=M+1:R=M-1}return-1}

// Unnecessarily compressed, no semicolons between statements, global vars, no clarity
arr=[1,3,5,7,9,11,13,15,17,19];x=13;
console.log("Found at index:",b(arr,x));

// “Creative” misuse of JavaScript syntax to add confusion
// Inline array, no whitespace, inline assignment, and ternary nesting
console.log((r=>r==-1?"Not found":`Found at ${r}`)(b([2,4,6,8,10,12,14,16],8)));
