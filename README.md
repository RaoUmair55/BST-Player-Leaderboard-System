# 🏆 BST Player Leaderboard System

A C++ console-based application that maintains a **player leaderboard** using a **Binary Search Tree (BST)**.  
Players are stored based on their **scores**, allowing efficient insert, update, delete, and search operations.

---

## 🚀 Features

### ✔ Maintain player scores using BST
Scores act as the primary key for BST placement  
(If scores are equal, player ID is used to avoid conflicts).

### ✔ Add Player  
Insert a new player with:
- Player ID  
- Player Name  
- Player Score  

### ✔ Delete Player  
Remove a player from the BST using their **score**.

### ✔ Update Player Score  
- Finds the player by old score  
- Deletes old record  
- Reinserts with new score  

### ✔ Search for Player  
Search by:
- **Player Name**
- **Player ID**

### ✔ Display Leaderboard  
Shows the full leaderboard in **descending order of scores**.

---

## 📂 Project Structure

📁 BST-Player-Leaderboard-System
│
├── main.cpp # Complete program source code
├── README.md # Project documentation


---

## 🧠 How It Works

### 1. **Insertion**
Players are inserted into the BST based on:
- Higher scores ⇒ go to the **right**
- Lower scores ⇒ go to the **left**

If scores are equal → player ID is used to break the tie.

### 2. **Deletion**
Handles all 3 BST deletion cases:
1. Node with no children  
2. Node with one child  
3. Node with two children (in-order successor)

### 3. **Searching**
Traversal-based search by ID or Name.

### 4. **Leaderboard Display**
Reverse Inorder Traversal (Right → Node → Left)  
ensures **highest scores appear first**.

---

## 📸 Sample Output (Preview)

------ Welcome ------

Add Player

Update Player Score

Delete Player Score

Display Leaderboard

Search player by name

Search player by ID

Exit

---

## 🛠 Technologies Used
- **C++**
- **Binary Search Trees (BST)**
- Console-based UI

---

## 🎯 Learning Outcomes
- Implementation of BST in a real-life application  
- Understanding node insertion, deletion, traversal  
- Searching objects inside tree structures  
- Clean code structuring using OOP (classes, getters/setters)

---

## 📜 License
This project is open-source.  
Feel free to use or modify it for your DSA or university project.

---

## 🤝 Contributing
Pull requests are welcome!

---

## 👤 Author
**Rao Umair Ahmed**

