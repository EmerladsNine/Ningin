# Ningin

# Project Name

## Code Style Guidelines

### Function Naming Conventions

- **Use PascalCase** for all function names (e.g., `GetPlayerPosition()`).
- **Verb-Noun** format should be used to make function purposes clear (e.g., `DrawCircle()`, `FetchData()`).
- **Boolean-returning functions** should be written as questions (e.g., `IsVisible()`, `HasCollision()`).
- **Accessor functions** should use `Get` and `Set` prefixes for retrieving and modifying properties (e.g., `GetScore()`, `SetVelocity()`).
- **Async functions** should end with `Async` (e.g., `FetchDataAsync()`).
- Avoid abbreviations, use full descriptive names (e.g., `CalculateTotal()` instead of `CalcTot()`).

### Additional Naming Conventions

- **Class names** should also follow PascalCase (e.g., `PlayerController`, `Vector2`).
- **Constants** should be written in ALL_CAPS with underscores (e.g., `MAX_HEALTH`, `DEFAULT_SPEED`).
- **Variables** should use camelCase for local variables (e.g., `playerScore`, `elapsedTime`).
- **File names** should match class names (e.g., `Vector2.cs` for a `Vector2` class).

### General Guidelines
- Functions should be descriptive but concise. Aim for names that clearly describe the action being performed.
- Maintain consistency across related functions (e.g., `AddItem()`, `RemoveItem()`, and `ClearItems()`).
