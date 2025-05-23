# 🌀 Meandres

**Meandres** is a first-person maze game developed entirely in **C++ using Unreal Engine**. Dive into a complex labyrinth filled with traps, collectibles, and time-based challenges. Your reflexes, decisions, and resource management skills will determine your survival.

---

## 🎮 Gameplay Overview

Navigate through a mysterious maze, collect coins, dodge traps, and find power-ups, all while racing against the clock. Each decision matters as you manage stamina and health to reach the exit before time runs out.

---

## 🧠 Features

### 🕹️ Movement & Core Systems
Implemented in the `PlayerCharacter` C++ class:
- Jump, run, and move in all directions.
- **Stamina System**: Pressing **Left Shift** doubles your speed at the cost of stamina.
- **Health System**: 
  - Starts at **100**.
  - Regenerates over time at a rate of **0.5f/sec**.
  - Reduced by trap damage.
- **Damage & Healing**:
  - Custom `TakeDamage()` function.
  - Health and stamina displayed on UI.

---

### 💰 Coin System
- `Coin`: +1 point.
- `DoubleCoin`: +2 points.
- Coins are created as C++ Actors and tracked on the UI.
- Some traps deduct coins as penalties.

---

### ⚠️ Traps & Hazards

| Trap          | Effect                                            | Notes                                             |
|---------------|---------------------------------------------------|---------------------------------------------------|
| **FirstTrap** | -13 HP                                            | Small. Can be jumped over.                        |
| **SecondTrap**| -33 HP, -1 Coin                                   | Cannot be jumped over. Damage even if jumped on.  |
| **LastTrap**  | -33 HP, -2 Coins                                  | Requires distance to bypass safely.              |
| **KillBlock** | Kills player after 5s delay                       | Audible "crunch" warns 2s before collapse.       |
| **SlowdownArea** | Reduces movement speed by 50%                  | Marked with a red X.                             |

---

### 💡 Power-Ups

| Power-Up         | Effect                         |
|------------------|--------------------------------|
| `HealthPowerUp`  | +15 HP (max 100)              |
| `StaminaPowerUp` | Fully restores stamina         |
| `TimePowerUp`    | +35 seconds to timer           |
| `LightPowerUp`   | Reveals shortest exit path     |

Each power-up is implemented as a custom C++ class.

---

### 🕒 Time System
- Game starts with **120 seconds**.
- Time displayed on the UI.
- If the timer reaches 0, the player loses.
- Timer can be extended by `TimePowerUp`.

---

### 🛠 Interactables

- `MovingPlatform`: Dynamic platforms with variable max/min heights.
- `SlidingDoors`: Opens based on player interactions.
- `Tutorial`, `Main Menu`, and `Credits` sections included.
- **Victory** and **Defeat** screens provide feedback at the end of each session.

---

## 💻 Built With

- **Unreal Engine**
- **C++**
  - Custom Character and Actor Classes
  - User Interface via UMG
  - Gameplay Programming & Event Systems

