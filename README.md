# **Project Title:** The Last Helldiver

**Group Members:**
• Muhammad Ateeb Ali (24K-0839)
• Syed Muhammad Muzammil Zaidi (24K-0887)
**Submission Date:** 11/05/2025

---

### 1. Executive Summary

**Overview:**
*The Last Helldiver* is a 2D battle royale game created in C++ using SFML. Developed as a semester project for Object-Oriented Programming, the game immerses players in a survival arena where enemies close in and a hellish fire zone shrinks the battlefield. It is a tribute to OOP principles applied in real-time gameplay through movement, AI, shooting, dynamic HUD, and zone mechanics.

**Key Findings:**
• Comprehensive application of OOP: encapsulation, inheritance, and abstraction.
• Delivered a fully interactive, audio-visual, SFML-based game with polish.
• Lore-intro, shooting sounds, fire zone, sprites, and HUD all successfully implemented.

---

### 2. Introduction

**Background:**
Battle royale games dominate the gaming world but often require vast resources. *The Last Helldiver* reimagines this genre as a focused, immersive 2D experience in C++, built around survival, minimalism, and Object-Oriented Programming.

**Project Objectives:**
• Build a playable 2D battle royale game with clear OOP design.
• Demonstrate principles of encapsulation, inheritance, and polymorphism.
• Implement movement, enemy AI, shooting mechanics, HUD, and shrinking zone.

---

### 3. Project Description

**Scope:**
**Included:**
• Player character with sprite-based movement
• Enemy AI pursuing the player
• Bullet firing with cooldown and collision detection
• Shrinking "fire" safe zone that damages player
• Sound effects for shooting
• HUD with score, kill count, and health
• Start screen and custom game-over screen

**Excluded:**
• Multiplayer gameplay
• Power-ups and weapon upgrades
• Advanced AI pathfinding and enemy diversity

**Technical Overview:**
• **Language:** C++
• **Library:** SFML (Simple and Fast Multimedia Library)
• **IDE:** Visual Studio Code
• **Assets:** Custom PNGs for sprites, background, and zone
• **Audio:** shoot.wav integrated via SFML
• **Version Control:** Git (local)

---

### 4. Methodology

**Approach:**
We used an iterative, agile-inspired method, dedicating each week to a core component: movement, bullets, enemies, HUD, zone, polish.

**Roles and Responsibilities:**
• **Muhammad Ateeb Ali:** Player logic, bullet system, shoot sound, HUD, UI polish, lore screen
• **Syed Muhammad Muzammil Zaidi:** Enemy AI, fire zone shrinking logic, collision handling

---

### 5. Project Implementation

**Design and Structure:**
• `Entity` base class for all game characters and objects
• `Player`, `Enemy`, and `Bullet` inherit and override behaviors
• `SafeZone` controls the fire zone logic

**Functionalities Developed:**
• WASD-based smooth player movement
• Enemy AI chases player
• Mouse-based bullet shooting with sound and cooldown
• Dynamic HUD with live stats
• Custom sprite and sound integration
• Game-over screen with background image and score file output

**Challenges Faced:**
• Player not taking damage initially due to collision logic
• Safe zone scaling incorrectly before coordinate recalibration
• Game loop not ending due to health-check bug
• Sprite and scaling alignment for custom textures

---

### 6. Results

**Project Outcomes:**
• A fully working single-player 2D battle royale game
• Complete encapsulation and real-world OOP application
• Polish in visual and auditory elements for better immersion

**Testing and Validation:**
• Manual testing for player-enemy and bullet-enemy collisions
• Timing tests for fire zone shrink rate and shooting cooldown
• UI element placement and responsiveness checked via varying resolutions

**Screenshots:**
![image](https://github.com/user-attachments/assets/c71f1d2b-a875-441c-ae8b-dd7452403423)

![image](https://github.com/user-attachments/assets/aae8aee4-032b-4b2a-8491-1532cf09a2ac)

![image](https://github.com/user-attachments/assets/64b45aca-a018-4fcf-b358-7ae34859888f)

![image](https://github.com/user-attachments/assets/e7616074-74a7-43e3-8187-996c1a5ba793)





---

### 7. Conclusion

**Summary of Findings:**
*The Last Helldiver* achieves all of its intended goals and even exceeds some — with aesthetic upgrades, sound, and structured OOP code.

**Final Remarks:**
We pushed the boundaries of what we thought possible in a C++ OOP semester project. From enemy AI to immersive fire zones, this project taught us game loops, object design, memory safety, and polish. We look forward to possibly expanding this into multiplayer or adding more strategic elements in the future.

---
