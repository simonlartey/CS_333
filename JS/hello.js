const greetings = [
    "Hello, World!",
    "Greetings, Universe!",
    "Hola, Mundo!",
    "Bonjour, le monde!",
    "Ciao, Mondo!"
  ];
  
  // Pick a random greeting
  const randomIndex = Math.floor(Math.random() * greetings.length);
  const greeting = greetings[randomIndex];
  
  // Print greeting with timestamp
  console.log(greeting + " (Generated at: " + new Date().toLocaleTimeString() + ")");