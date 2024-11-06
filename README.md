
---

# Monopoly Game Project

This project is an implementation of the Monopoly game using the SFML graphics library in C++. It allows players to move around the board, purchase properties, pay rent, and perform other actions according to the game rules.

## Project Features

- **Dynamic Game Board**: Implements a game board with cities and streets from Israel, such as Kiryat Ata, Ariel, Netanya, Haifa, Jerusalem, Tel Aviv, and Savion.
- **Player Movement**: Players move based on dice rolls and can perform actions like buying houses and hotels.
- **Money and Rent Management**: Players earn money and pay rent based on their position on the board.
- **Graphical Interface**: Communication with players is via a GUI with windows, buttons, and messages.
- **Chance and Surprise Cards**: "Chance" cards add unexpected elements to the game.
- **Jail and Tax Squares**: Handles jail, taxes, and "Free Parking" according to the game rules.

## Project Structure

- **GameFlow Class**: Manages game flow, player turns, and status. It interacts with the GUI, updating the board after each turn.
- **Square Class**: Base class for board squares (including streets, properties, and special squares).
- **SpecialSquare Class**: Represents special squares like jail, tax, chance, and free parking.
- **Player Class**: Manages each player's data, such as color, name, ID, and properties. It also interfaces with the GUI for displaying the player's position, assets, and available cash.
- **Board Class**: Singleton class responsible for creating and displaying the game board in the GUI.
- **Button Class**: Creates clickable buttons used by other classes for player interaction.
- **Estate Class**: Abstract class representing purchasable assets.
- **Street Class**: Represents a buyable street, allowing interaction for house or hotel upgrades via the GUI.
- **Infrastructure Class**: Represents purchasable infrastructure (like utilities and railroads).

### Class Hierarchy

- All board-related classes inherit from **Square**:
  - **SpecialSquare** and **Estate** directly inherit from **Square**.
  - **Street** and **Infrastructure** inherit from **Estate**.

- The `GameFlow` class encapsulates all others to manage the game’s operation seamlessly.

## Core Method

- **Action**: Defined in the `Square` class, this method performs specific actions for each square (e.g., going to jail, buying assets, paying rent, and upgrading to hotels).

## Running the Game

When you start the game, you’ll enter the number of players (2-8) through the GUI. Each player takes turns rolling dice and moving around the board. Actions required based on their positions, like purchasing properties, paying rent, or drawing Chance cards, are shown as messages. The game ends when only one player remains financially solvent, or one player reaches +4000 units of currency.

### GUI Guide

- On starting the game, follow instructions to add players. Each player’s name and color are input in sequence.
- The GUI displays player cash and assets on the board. To view player estates, click "VIEW Estates."
- To start a turn, click "Roll Dice." Follow prompts for required actions based on the square landed.
- Timers appear with some messages to allow reading time. When rolling dice, wait for the message to clear before proceeding.
- Winning is automatically detected, ending the game when applicable.

Good luck!

