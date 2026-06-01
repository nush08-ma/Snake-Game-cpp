# Snake-Game-cpp
## Snake Game (C++)A classic, lightweight, and responsive Snake game built entirely in C++ for the Windows Console. This project leverages the Windows API to control console cursor positioning, allowing for smooth, real-time rendering without standard screen flickering.

## FeaturesSmooth CLI Rendering: 
Uses the Windows Console API (SetConsoleCursorPosition) to draw characters instantly, ensuring fluid gameplay.

Dynamic Screen Bounds: Automatically detects your current console window dimensions and adapts the gameplay boundaries accordingly.

Self-Collision Detection: Classic rules apply—if the snake bites its own tail, the game ends.

Real-time Input Handling: Uses non-blocking input (kbhit and getch) for crisp and immediate directional control.

Score Tracker: Keeps a live count of your current score at the top of the terminal.

## ControlsUse standard WASD keys to navigate the snake around the console screen:
| Key | Action | Opposite Restriction |
| :---: | :--- | :--- |
| **`W` / `w`** | Move **UP** | Cannot move directly into **DOWN** |
| **`A` / `a`** | Move **LEFT** | Cannot move directly into **RIGHT** |
| **`S` / `s`** | Move **DOWN** | Cannot move directly into **UP** |
| **`D` / `d`** | Move **RIGHT** | Cannot move directly into **LEFT** |

## Code ArchitectureThe project is structured using clean Object-Oriented Programming (OOP) principles:
Point Struct: Represents 2D coordinates (x, y) on the console grid.

Snake Class: Manages the snake's state, length growth, self-collision logic, and direction constraints (e.g., preventing the snake from reversing directly into itself).

Board Class: Orchestrates the overall game loop. It handles randomized food spawning, updating the positions, capturing real-time user inputs, and rendering game elements (O for the snake body and # for food).
