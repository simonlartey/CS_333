/*
 * File: sql_extension.sql
 * Author: Simon Lartey
 * Date: 10/21/2025
 *
 * Description:
 * Demonstrates SQL’s declarative syntax, variable scoping, and lifetime using
 * stored procedures, local variables, and aggregate functions.
 */

-- Create a sample database and switch to it
CREATE DATABASE IF NOT EXISTS school;
USE school;

-- Create a table to hold student grades
CREATE TABLE Students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50),
    grade INT
);

-- Insert sample data
INSERT INTO Students (name, grade) VALUES
('Alice', 85),
('Ben', 72),
('Carla', 93),
('David', 64),
('Ella', 88);

-- ======================================
-- Example 1: Aggregate functions in SQL
-- ======================================
SELECT
    COUNT(*) AS total_students,
    AVG(grade) AS average_grade,
    MAX(grade) AS highest_grade,
    MIN(grade) AS lowest_grade
FROM Students;


-- ======================================
-- Example 2: Variable declaration and scope
-- ======================================
DELIMITER $$

CREATE PROCEDURE ShowStudentStats()
BEGIN
    DECLARE avg_grade DECIMAL(5,2);
    DECLARE high_grade INT;

    -- Assign values to local variables
    SELECT AVG(grade) INTO avg_grade FROM Students;
    SELECT MAX(grade) INTO high_grade FROM Students;

    -- Output using SELECT
    SELECT CONCAT('Average Grade: ', avg_grade) AS 'Average Grade Info';
    SELECT CONCAT('Highest Grade: ', high_grade) AS 'Highest Grade Info';
END$$

DELIMITER ;

-- Call the procedure
CALL ShowStudentStats();


-- ======================================
-- Example 3: Demonstrating lifetime and session-level scope
-- ======================================

-- Create a session variable
SET @school_name = 'Greenfield Academy';

-- Access the variable anywhere in this session
SELECT @school_name AS 'Session Variable';

-- Define a procedure with a local variable of the same name
DELIMITER $$

CREATE PROCEDURE ShowSchoolInfo()
BEGIN
    DECLARE school_name VARCHAR(50);
    SET school_name = 'Local Variable Inside Procedure';
    SELECT school_name AS 'Local Scope Variable';
END$$

DELIMITER ;

-- Call the procedure (uses local variable)
CALL ShowSchoolInfo();

-- Check the global session variable (still unchanged)
SELECT @school_name AS 'Session Variable Still Active';
