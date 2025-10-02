# Turtix Game

A 2D platformer game inspired by the classic Turtix series, implemented in C++ using the SFML graphics library. This project demonstrates advanced programming concepts including object-oriented design, inheritance, polymorphism, and game development patterns.

## 🎮 Game Overview

Turtix is a side-scrolling platformer where players control a turtle character navigating through challenging levels filled with enemies, collectibles, and obstacles. The goal is to collect points while avoiding or defeating enemies and ultimately reach the portal to complete the level.

### Game Features

- **Dynamic Animation System**: Smooth character animations with multiple states (idle, walking, jumping, falling, climbing, etc.)
- **Multiple Enemy Types**: Three distinct enemy types with unique behaviors and AI patterns
- **Collectible System**: Stars (1000 points) and diamonds (5000 points) scattered throughout the level
- **Physics-Based Movement**: Realistic jumping, falling, and collision detection
- **Background Music**: Immersive audio experience with looping background music
- **Level Design**: Map-based level loading system using text files
- **Health System**: Player has 3 lives with damage states and ghost mode
- **Win/Lose Conditions**: Complete objectives to win or lose all lives for game over

## 🏗️ Project Structure

### Core Classes

#### `Game` Class
- **Purpose**: Main game engine that manages the game loop, rendering, and game state
- **Key Features**:
  - Window management and event handling
  - Terrain generation from map files
  - Enemy spawn and management system
  - Collision detection and physics
  - Audio system integration
  - Game state management (playing, winning, losing)

#### `Animated` Class (Base Class)
- **Purpose**: Abstract base class for all animated game objects
- **Key Features**:
  - Frame-based animation system
  - Sprite management and scaling
  - Movement and positioning
  - Animation state management
  - Input handling for controllable objects

#### `Player` Class
- **Purpose**: Player character with full animation and control system
- **Inherits**: `Animated`
- **Key Features**:
  - 12 different animation states (idle, walking, jumping, falling, swinging, pushing, pulling, damaged, climbing, etc.)
  - Health and points system
  - Directional movement and jumping mechanics
  - Ghost mode when damaged
  - Portal entry animations

#### Enemy Classes

##### `Baby` Class
- **Purpose**: Basic enemy with simple movement patterns
- **States**: Frozen, Moving
- **Behavior**: Moves left and right, can fall off platforms
- **Animation**: Two-frame movement animation

##### `AdvancedEnemy` Class
- **Purpose**: Intelligent enemy with advanced behaviors
- **States**: Ordinary, Unbeatable
- **Behavior**: More complex AI patterns, temporary invulnerability phases
- **Special**: Clock-based state switching

##### `DoublelifeEnemy` Class
- **Purpose**: Enemy that requires two hits to defeat
- **States**: Two Lives, One Life
- **Behavior**: Changes appearance and behavior after first collision
- **Special**: Dual-state system with different sprites

#### Environment Classes

##### `Point` Class
- **Purpose**: Collectible items for scoring
- **Types**: 
  - Stars (1000 points)
  - Diamonds (5000 points)
- **Animation**: Animated collectibles with sparkle effects

##### `Portal` Class
- **Purpose**: Level exit that can be opened/closed
- **States**: Open, Closed
- **Behavior**: Player entry triggers level completion

##### `Ground` & `Tile` Classes
- **Purpose**: Level geometry and collision surfaces
- **Features**: Tilemap system for efficient level design

## 🎯 Game Mechanics

### Controls
- **A**: Move left
- **D**: Move right  
- **W**: Jump
- **Space**: Restart game (when game ends)

### Map Legend
```
. = Ground/Platform
$ = Portal (level exit)
O = Baby enemy spawn
E = Doublelife enemy spawn  
M = Advanced enemy spawn
^ = Diamond (5000 points)
* = Star (1000 points)
(space) = Empty air
```

### Scoring System
- **Stars**: 1000 points each
- **Diamonds**: 5000 points each
- **Objective**: Collect points while navigating to the portal

### Health System
- **Starting Health**: 3 lives
- **Damage**: Contact with enemies reduces health
- **Ghost Mode**: Temporary invulnerability after taking damage
- **Game Over**: Health reaches 0

## 🛠️ Technical Implementation

### Dependencies
- **SFML 2.x**: Graphics, Audio, Window, and System modules
- **C++11 or later**: Modern C++ features
- **Standard Library**: File I/O, containers, algorithms

### Design Patterns Used
- **Inheritance Hierarchy**: Base `Animated` class with specialized derived classes
- **Polymorphism**: Virtual functions for update and render methods
- **Composition**: Game class contains collections of all game objects
- **State Machine**: Animation and behavior state management
- **Resource Management**: RAII principles for texture and sound management

### Key Algorithms
- **Collision Detection**: AABB (Axis-Aligned Bounding Box) collision system
- **Animation System**: Frame-based sprite animation with timing controls
- **Physics Simulation**: Basic gravity and movement physics
- **AI Behaviors**: State-based enemy movement patterns

### File I/O
- **Map Loading**: Text-based level format for easy level design
- **Resource Loading**: Sprite sheets, textures, fonts, and audio files
- **Configuration**: Constants file for easy gameplay tuning

## 🚀 Building and Running

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install libsfml-dev

# Arch Linux  
sudo pacman -S sfml

# macOS (with Homebrew)
brew install sfml
```

### Compilation
```bash
# Using provided Makefile
make

# Manual compilation
g++ -c *.cpp
g++ *.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o turtix.out
```

### Running the Game
```bash
./turtix.out
```

### Clean Build
```bash
make clean
```

## 📁 Assets

### Sprites
- Character animations (walking, jumping, climbing, etc.)
- Enemy sprites with multiple frames
- Environmental textures (ground, background)
- Collectible item animations
- Portal states (open/closed)

### Audio
- Background music (`music.ogg`)
- Sound effects integration ready

### Fonts
- Game UI font (`font.ttf`)

## 🎨 Graphics and Animation

### Animation System
- **Frame-based Animation**: Each character has multiple animation states
- **Sprite Sheets**: Efficient texture usage with frame rectangles
- **Animation Timing**: Configurable frame rates (150ms per frame default)
- **Direction Handling**: Automatic sprite flipping for left/right movement
- **Scale Factors**: Consistent sizing across all game objects

### Visual Effects
- **Ghost Mode**: Alpha transparency effects for damage states
- **Portal Animation**: Scaling effects for level completion
- **Background**: Parallax-ready background system
- **UI Elements**: Score display and game state messages

## 🔧 Configuration

### Constants (`Constants.hpp`)
```cpp
ANIMATION_MILLISECONDS_PER_FRAME = 150    // Animation speed
PLAYER_SPEED = 50.f                       // Player movement speed  
BABY_SPEED = 50.f                        // Baby enemy speed
ENEMY_SPEED = 25.f                       // Advanced enemy speed
PLAYER_JUMP_SECONDS = 1.75f              // Jump duration
STAR_POINTS = 1000                       // Star value
DIAMOND_POINTS = 5000                    // Diamond value
```

### Customization
- Modify `map.txt` to create new levels
- Adjust constants for different gameplay feel
- Replace sprite files for visual customization
- Change audio files for different atmosphere

## 🧩 Object-Oriented Design

### Inheritance Hierarchy
```
Animated (Base Class)
├── Player
├── Baby  
├── AdvancedEnemy
├── DoublelifeEnemy
└── Point

Tile (Base Class)
├── Ground
└── Portal
```

### Polymorphism Examples
- Virtual `update()` methods for different object behaviors
- Virtual `render()` methods for specialized drawing
- Unified interface for all animated objects

### Encapsulation
- Private member variables with public accessors
- Protected inheritance for shared functionality
- Clear separation of concerns between classes
