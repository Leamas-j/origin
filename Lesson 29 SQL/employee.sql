CREATE TABLE IF NOT EXISTS Employee (
    id INT PRIMARY KEY,         
    name VARCHAR(100) NOT NULL,  
    department VARCHAR(100),    
    manager_id INT NULL,        
    FOREIGN KEY (manager_id) REFERENCES Employee(id)
);