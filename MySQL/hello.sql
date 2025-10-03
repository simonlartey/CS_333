CREATE TEMPORARY TABLE greetings (
    language VARCHAR(20),
    message  VARCHAR(50)
);

INSERT INTO greetings VALUES
('English', 'Hello, World!'),
('Spanish', 'Hola, Mundo!'),
('French', 'Bonjour, le monde!'),
('Italian', 'Ciao, Mondo!');

SELECT language, message FROM greetings;
