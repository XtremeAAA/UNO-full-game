# UNO Terminal Game in C

A terminal-based implementation of the classic **UNO** game written in **C**. The game allows you to play with a human and a computer opponent. Key features include **+2**, **+4**, and **Reverse** cards that affect the flow of the game.

---

## 🎮 Game Modes

This game offers 3 possible modes:

1. **Human vs Human**  
   Two players take turns entering their moves.

2. **Human vs Computer**  
   The computer plays randomly, simulating an opponent.

3. **Computer vs Computer**  
   Both players are AI-controlled. A good choice for testing the game's logic.

### 🏆 Match Format:
- **First to 4 wins**  
  The game continues until either the player or computer wins 4 rounds.

---

## 🔹 Game Mechanics

- **Deck Composition**  
  The game uses a deck consisting of color cards (Red, Green, Blue, Yellow), as well as wild cards. Each color contains cards numbered 0-9, special **+2**, **+4**, and **Reverse** cards.
  
- **Gameplay**  
  The game starts with 7 cards for both the player and the computer. Players take turns playing cards, with the objective of matching the top card either by number or color. Special cards like **+2** and **+4** affect the opponent, forcing them to draw cards or skip their turn.

---

## 🔸 Special Card Mechanics

1. **+2 Cards**  
   The opponent must draw 2 cards and their turn is skipped.

2. **+4 Cards**  
   The opponent must draw 4 cards and their turn is skipped. The top card can be changed to any color.

3. **Reverse Cards**  
   The direction of play is reversed.

---

## 🛠️ How to Compile and Run

Make sure you have a C compiler (e.g., `gcc`).

### ✅ Compile:
```bash
gcc -o uno_game uno_game.c
