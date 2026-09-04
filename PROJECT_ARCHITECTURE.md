# PYTHON AWAKENING: THE CODE REALM
## Unreal Engine 5 Project Architecture

---

## PROJECT OVERVIEW

**Genre:** AAA Open-World Fantasy Adventure RPG with Python Education  
**Engine:** Unreal Engine 5 (C++ & Blueprints)  
**Target Platform:** Windows/Linux/Mac/Console  
**Development Model:** Modular, expandable architecture  

---

## PHASE 1: VERTICAL SLICE (Current Focus)
### Deliverable: Playable beginning-to-end experience (Variable Valley Region)

**Timeline:** 3-4 months  
**Scope:** One complete region with all core systems

#### Phase 1 Milestones:
- [ ] UE5 Project setup & C++ foundation
- [ ] Player character system with customization
- [ ] Third-person movement & camera
- [ ] Save/profile system
- [ ] Mini-map & compass HUD
- [ ] One village with NPCs
- [ ] One tavern with NPC dialogue
- [ ] Adventurer Guild basic structure
- [ ] Python runtime integration (sandboxed)
- [ ] First programming lesson (Variables)
- [ ] Coding challenge system
- [ ] Combat system (action-RPG + code-based)
- [ ] One dungeon with puzzles
- [ ] First boss: Variable Guardian
- [ ] Achievement/title system
- [ ] Quest system (main, side, guild)
- [ ] High-quality graphics & polish
- [ ] Save/load gameplay loop
- [ ] End-to-end playable experience

---

## CORE SYSTEMS ARCHITECTURE

```
PythonAwakening/
├── Source/
│   ├── PythonAwakening/
│   │   ├── Core/
│   │   │   ├── GameMode/
│   │   │   │   └── PAGameMode.h/cpp
│   │   │   ├── GameState/
│   │   │   │   └── PAGameState.h/cpp
│   │   │   └── PlayerController/
│   │   │       └── PAPlayerController.h/cpp
│   │   │
│   │   ├── Character/
│   │   │   ├── PACharacter.h/cpp
│   │   │   ├── CharacterCustomization.h/cpp
│   │   │   ├── CharacterMovement.h/cpp
│   │   │   └── Animations/
│   │   │
│   │   ├── Python/
│   │   │   ├── PythonRuntime.h/cpp (sandboxed execution)
│   │   │   ├── CodeValidator.h/cpp
│   │   │   ├── OutputConsole.h/cpp
│   │   │   └── TestCaseRunner.h/cpp
│   │   │
│   │   ├── Combat/
│   │   │   ├── CombatSystem.h/cpp
│   │   │   ├── CodeBasedAttack.h/cpp
│   │   │   ├── Enemy.h/cpp
│   │   │   ├── Boss.h/cpp
│   │   │   └── StatusEffect.h/cpp
│   │   │
│   │   ├── Quest/
│   │   │   ├── QuestSystem.h/cpp
│   │   │   ├── Quest.h/cpp
│   │   │   ├── QuestLog.h/cpp
│   │   │   └── ObjectiveTracker.h/cpp
│   │   │
│   │   ├── NPC/
│   │   │   ├── NPCBase.h/cpp
│   │   │   ├── NPCBehaviour.h/cpp
│   │   │   ├── Dialogue.h/cpp
│   │   │   └── Routines/
│   │   │
│   │   ├── World/
│   │   │   ├── WeatherSystem.h/cpp
│   │   │   ├── DayNightCycle.h/cpp
│   │   │   └── WorldEvents.h/cpp
│   │   │
│   │   ├── UI/
│   │   │   ├── HUD/
│   │   │   │   ├── MainHUD.h/cpp
│   │   │   │   ├── MiniMap.h/cpp
│   │   │   │   ├── Compass.h/cpp
│   │   │   │   └── CodingTerminal.h/cpp
│   │   │   ├── Menus/
│   │   │   │   ├── MainMenu.h/cpp
│   │   │   │   ├── PauseMenu.h/cpp
│   │   │   │   └── SettingsMenu.h/cpp
│   │   │   └── Widgets/
│   │   │
│   │   ├── Save/
│   │   │   ├── SaveSystem.h/cpp
│   │   │   ├── PlayerProfile.h/cpp
│   │   │   └── SaveData.h/cpp
│   │   │
│   │   ├── Inventory/
│   │   │   ├── InventorySystem.h/cpp
│   │   │   ├── Item.h/cpp
│   │   │   ├── Equipment.h/cpp
│   │   │   └── ItemDatabase.h/cpp
│   │   │
│   │   ├── Progression/
│   │   │   ├── ProgressionSystem.h/cpp
│   │   │   ├── PythonSkillTree.h/cpp
│   │   │   ├── Achievement.h/cpp
│   │   │   └── Title.h/cpp
│   │   │
│   │   ├── Education/
│   │   │   ├── LessonSystem.h/cpp
│   │   │   ├── Lesson.h/cpp
│   │   │   ├── CodingChallenge.h/cpp
│   │   │   └── HintSystem.h/cpp
│   │   │
│   │   ├── Audio/
│   │   │   ├── AudioManager.h/cpp
│   │   │   └── MusicSystem.h/cpp
│   │   │
│   │   └── Cinematics/
│   │       ├── CinematicSequencer.h/cpp
│   │       └── DialogueSequence.h/cpp
│   │
│   └── PythonAwakening.Build.cs
│
├── Content/
│   ├── Maps/
│   │   ├── MainMenu/
│   │   ├── VariableValley/
│   │   └── Cinematics/
│   ├── Characters/
│   ├── Environments/
│   ├── Assets/
│   ├── Materials/
│   ├── Textures/
│   ├── Blueprints/
│   └── Audio/
│
├── Binaries/
├── Intermediate/
├── Saved/
├── Plugins/
│   └── PythonPlugin/ (Custom Python integration)
│
├── .gitignore (UE5 specific)
├── PythonAwakening.uproject
└── README.md
```

---

## CORE SYSTEMS DESCRIPTIONS

### 1. CHARACTER SYSTEM
- **PACharacter**: Main player character
- **CharacterCustomization**: Face, hair, clothing, equipment
- **CharacterMovement**: WASD movement, sprint, jump, crouch, dodge
- **State Management**: Combat state, exploration state, dialogue state

### 2. PYTHON RUNTIME SYSTEM
**Most Critical System**

```
User writes Python code in Terminal UI
     ↓
PythonRuntime receives code
     ↓
Syntax validation (catches SyntaxError immediately)
     ↓
Run in sandboxed environment (no file/network/OS access)
     ↓
Capture output
     ↓
Validate against test cases
     ↓
Return result (success/error)
     ↓
Apply result to game world (damage, heal, etc.)
```

**Safety Requirements:**
- No `import os`, `import sys`, `open()`, `socket`, `subprocess`
- Limited built-in functions (only safe ones)
- Execution timeout (prevent infinite loops)
- Memory limit
- No external module access

### 3. COMBAT SYSTEM
**Action-RPG + Code-Based**

```
Basic Combat (traditional):
  - Left-click: basic attack
  - Right-click: heavy attack
  - Space: dodge
  - E: block

Code-Based Combat (powerful):
  - K: open Python terminal
  - Write attack code
  - Press RUN
  - Code executes in world
  - Result: custom damage, effects, combos
```

**Example Combat Code:**
```python
damage = 25
for i in range(3):
    attack(target, damage)
```
Result: 3 attacks of 25 damage each

### 4. QUEST SYSTEM
- **Main Quest**: Story progression (discover Creator identity)
- **Side Quest**: NPC stories, world lore
- **Guild Quest**: Monster hunts, programming challenges
- **Tavern Quest**: Rumors, mysterious encounters
- **Python Challenge**: Pure programming puzzles

### 5. SAVE SYSTEM
**Critical: Never overwrite player data**

```
Player enters name → Validates name (3-25 chars, 1 upper, 1 lower, 1 number)
     ↓
Generate unique internal ID
     ↓
Check if profile exists:
  - Yes: Show options (NEW/CONTINUE/LOAD/DELETE)
  - No: Create new profile
     ↓
Save structure:
{
  "player_name": "Alex7Coder",
  "internal_id": "UUID",
  "created_at": timestamp,
  "last_played": timestamp,
  "level": int,
  "xp": int,
  "position": Vector3D,
  "inventory": [...],
  "quests": {...},
  "achievements": [...],
  "python_knowledge": {...},
  "world_state": {...},
  "discovered_locations": [...]
}
```

### 6. NPC SYSTEM
- **NPCBase**: All NPCs inherit from this
- **Daily Routines**: Wake → Work → Eat → Rest
- **Dialogue Trees**: Branching conversations
- **Relationship System**: Track NPC opinions
- **Quest Givers**: NPCs offer quests

### 7. WORLD SYSTEM
- **Day/Night Cycle**: 48 minutes = 1 full cycle (24 hours)
- **Weather System**: Random/event-based weather changes
- **World Events**: Time-based story events
- **Environmental Storytelling**: Murals, ruins, lore items

### 8. UI/HUD SYSTEM
- **Main HUD**: Health, stamina, coding energy, XP, quest marker
- **Mini-Map**: Shows nearby NPCs, quest markers, points of interest
- **Compass**: Cardinal directions + quest direction
- **Coding Terminal**: Full-featured Python IDE integrated into game
- **Menus**: Main menu, pause, settings, inventory, map, achievements

### 9. PROGRESSION SYSTEM
- **Levels**: 1-50 (each region has boss)
- **XP Gains**: Combat, quests, puzzles, discoveries
- **Python Skill Tree**: 8 categories (Foundations, Logic, Iteration, Functions, Data, Reliability, Architecture, Advanced)
- **Titles**: Unlock with each boss defeat
- **Achievements**: 50+ unlockable

### 10. EDUCATION SYSTEM
- **Lesson Manager**: Trigger lessons naturally in gameplay
- **Progressive Teaching**: Print → Variables → Data Types → ... → Classes → Algorithms
- **Integrated Learning**: Learn by doing (repair machines, solve puzzles)
- **Hint System**: Progressive hints, not automatic solutions
- **Test Cases**: Validate player code correctness

---

## DEVELOPMENT PHASES

### PHASE 1: VERTICAL SLICE (Months 1-4)
✅ Complete playable experience (Variable Valley region)
- All core systems functional
- One region fully polished
- One complete gameplay loop

### PHASE 2: REGION EXPANSION (Months 5-8)
- Logic Wilds region
- Looping Marshes region
- Function Citadel region

### PHASE 3: ADVANCED REGIONS (Months 9-12)
- Dataforge region
- Exceptional Abyss region
- Object Kingdom region

### PHASE 4: FINAL CHAPTER (Months 13-16)
- Corrupted Core region
- Returning boss battles
- Null encounter
- Ending cinematics

### PHASE 5: POLISH & RELEASE (Months 17-18)
- Quality assurance
- Performance optimization
- Audio/music implementation
- Final balancing

---

## TECHNOLOGY STACK

- **Engine**: Unreal Engine 5
- **Language**: C++ (systems), Blueprints (gameplay)
- **Python Integration**: Embedded Python runtime (sandboxed)
- **Serialization**: JSON for save data
- **Animation**: Sequencer for cinematics
- **Audio**: WAV/OGG asset support
- **UI**: UMG (Unreal Motion Graphics)

---

## ASSET REQUIREMENTS (To Be Sourced)

### Characters
- Player character model (customizable)
- 20+ NPC models with variations
- Boss models (8 unique)
- Enemy creatures (20+ types)

### Environments
- Variable Valley (rolling hills, forests)
- Villages with interiors
- Taverns with detailed assets
- Dungeons with unique themes
- Castles, temples, labs

### Audio
- Dynamic soundtrack (8+ tracks)
- Environmental ambient sounds
- Combat sound effects
- UI/interaction sounds
- Voice acting (optional)

### Visual Effects
- Combat effects
- Magic effects
- Weather effects
- Particle systems
- Post-processing

---

## SUCCESS METRICS (Phase 1)

✅ Core gameplay loop: Explore → Learn → Practice → Fight → Win (30 min)  
✅ Python runtime executes 50+ valid Python concepts  
✅ Combat feels responsive and satisfying  
✅ Dialogue system fully functional  
✅ Save/load works perfectly without data loss  
✅ Mini-map displays all discovered locations  
✅ Boss fight cinematically engaging  
✅ Graphics quality competitive with indie AAA standards  
✅ No critical bugs or crashes  
✅ Educational progression clear and rewarding  

---

## NEXT IMMEDIATE STEPS

1. ✅ Create GitHub repository
2. 🔄 **SET UP UE5 PROJECT** (in progress)
3. Implement Python Runtime System
4. Build Core Character System
5. Create Player Movement & Camera
6. Design Save System
7. Build Basic HUD
8. Create First NPC + Dialogue
9. Implement Quest System
10. Build Python Terminal UI

---

## NOTES

- All systems are designed to be **modular and expandable**
- Each system can be developed in parallel
- Quality over quantity - polish each system before moving to next
- Regular playtesting at each milestone
- Community feedback integration point: Phase 2
