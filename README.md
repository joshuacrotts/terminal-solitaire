<h1 align="center">Terminal Solitaire</h1>

<p align="center">
  <img width="622" height="350" src="docs/soltaire.gif">
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/joshuacrotts/Terminal-Solitaire/badge)](https://www.codefactor.io/repository/github/joshuacrotts/Terminal-Solitaire) ![GitHub contributors](https://img.shields.io/github/contributors/JoshuaCrotts/Terminal-Solitaire) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/JoshuaCrotts/Terminal-Solitaire) ![GitHub repo size](https://img.shields.io/github/repo-size/JoshuaCrotts/Terminal-Solitaire)  ![](https://tokei.rs/b1/github/JoshuaCrotts/Terminal-Solitaire) ![](https://tokei.rs/b1/github/JoshuaCrotts/Terminal-Solitaire?category=files) [![GitHub issues open](https://img.shields.io/github/issues/JoshuaCrotts/Terminal-Solitaire)]() 
[![GitHub issues closed](https://img.shields.io/github/issues-closed-raw/JoshuaCrotts/Terminal-Solitaire)]()

Terminal - Solitaire is an implementation of the classic Solitaire game... but in the terminal! Instead of dragging cards around the screen, commands are used to move cards from the stock to waste, foundations, and layouts. 

## Dependencies

The only dependency for this project is the ncurses library, which is preinstalled on most Linux distributions.

## Rebuilding Terminal - Standards

**Linux**: To rebuild the code, clone the repository to your computer. Assuming that you have ncurses installed, the project should compile without question.

## Known Issues
There are some inconsistencies in the codebase; the parsing file is not the most efficient, there may be some memory leaks but I haven't verified this with Valgrind. Plus, it's possible to move any card to any deck at this time. Functions that serve as rules (e.g. blocking same-color cards on top of each other in a layout, prohibiting non-same suit cards in a foundation) do exist, but are yet to be implemented in the code.

## Reporting Bugs

See the Issues Tab.

## Version History
The **master** branch encompasses all significant changes. The **development** branch has in-progress additions and updates that are not yet ready for the master branch.
