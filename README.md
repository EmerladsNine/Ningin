# Ningin

## Code Style Guidelines

### Function Naming Conventions

- $\color{#FF6347}{\textsf{1. Use PascalCase}}$ for all function names.
- $\color{#FF6347}{\textsf{2. Verb-Noun}}$ Functions often perform actions, so it’s common to use a verb followed by a noun to describe what the function does.
- $\color{#FF6347}{\textsf{3. Descriptive but Concise}}$ Function names should be descriptive enough to understand what they do but not overly verbose.
- $\color{#FF6347}{\textsf{4. Use Domain-Specific Terms}}$ If a function is related to a particular domain (e.g. physics), using terms from that domain can help.
- $\color{#FF6347}{\textsf{5. Action-Oriented Naming}}$ Functions should represent actions, so using strong action verbs is ideal.
- $\color{#FF6347}{\textsf{6. Boolean-returning functions}}$ For functions that return a boolean, the name should reflect a yes/no question. (e.g., `IsVisible()`, `HasCollision()`).
- $\color{#FF6347}{\textsf{7. Accessor functions}}$ should use `Get` and `Set` prefixes for retrieving and modifying properties (e.g., `GetScore()`, `SetVelocity()`).

* $\color{#FF6347}{\textsf{8. Follow the Command-Query Separation principle:}}$
  * $\color{#FF6347}{\textsf{Commands}}$: Functions that perform actions (usually without returning a value) - Example: `MovePlayer()`
  * $\color{#FF6347}{\textsf{Queries}}$: Functions that return values or answer questions. - Example: `GetScore()`, `IsGameOver()`
- $\color{#FF6347}{\textsf{9. Avoid abbreviations}}$, use full descriptive names (e.g., `CalculateTotal()` instead of `CalcTot()`).
---
### Additional Naming Conventions

- **Classes (Structs and Enums too) names** should also follow $\color{#FF6347}{\textsf{PascalCase}}$.
- **Constants** should be written in $\textcolor{#FF6347}{\textsf{CAMELˍCASE}}$ format.
- **Variables:** 
  * $\color{#FF6347}{\textsf{1. Public variables}}$ should be written in $\color{#FF6347}{\textsf{camelCase}}$ format.
  * $\color{#FF6347}{\textsf{2. Private variables}}$ should be written in $\color{#FF6347}{\textsf{ˍcamelCase}}$ format.
  * $\color{#FF6347}{\textsf{3. Ascribe a name}}$ to each variable that clearly describes its purpose.
  * $\color{#FF6347}{\textsf{4. A single variable}}$ can’t be assigned various values in multiple contexts.
- **File names** should match **class/struct/enum names** (e.g. `Vector2.h` for a `Vector2` class).
---
### Add Comments:
- $\color{#4682B4}{\textsf{To clarify complex or obscure code sections}}$
- $\color{#4682B4}{\textsf{To areas where improvements or additional features need to be implemented.}}$
- $\color{#4682B4}{\textsf{To explain domain-specific logic}}$
---
### Refrain From Adding Comments:
- $\color{#FF4500}{\textsf{That merely repeat what the code already expresses clearly.}}$
- $\color{#FF4500}{\textsf{When code’s purpose is evident.}}$
---
### General Guidelines
- Maintain $\color{#32CD32}{\textsf{consistency}}$ across related functions (e.g. `AddItem()`, `RemoveItem()`, and `ClearItems()`).
- Avoid $\color{#32CD32}{\textsf{Deep Nesting}}$. To maintain readability, aim for no more than 3 levels of nesting.
- Avoid $\color{#32CD32}{\textsf{Multi-Task functions}}$: a single function should carry out a single task.
- Use the $\color{#32CD32}{\textsf{DRY (Don’t Repeat Yourself)}}$ principle, the same piece of code should not be repeated.
- Add $\color{#32CD32}{\textsf{Comments}}$ for explaining the logic, functionality, or the purpose of specific sections.
- Divide the code into smaller self-contained modules and functions to enhance $\color{#32CD32}{\textsf{reusability}}$ and $\color{#32CD32}{\textsf{maintainability}}$.
- Each $\color{#32CD32}{\textsf{class}}$ or $\color{#32CD32}{\textsf{struct}}$ should be in its own file.
---
### Rust Style Guidelines
- $\color{#FF4500}{\textsf{Formatting}}$: Follow the standard Rust formatting conventions. Use `rustfmt` to ensure code is consistently formatted.
- $\color{#FF4500}{\textsf{Naming Conventions:}}$
  * **Functions and Methods:** Use $\color{#FF4500}{\textsf{camelˍcase}}$ for function and method names.
  * **Structs and Enums:** Use $\color{#FF4500}{\textsf{PascalCase}}$ for struct and enum names.
  * **Constants and Static Variables:** Use $\color{#FF4500}{\textsf{CAMELˍCASE}}$ for constants and static variables.
- $\color{#FF4500}{\textsf{Error Handling:}}$ Use `Result` and `Option` types for functions that can return an error or an optional value. Avoid panicking unless it’s a critical failure.
---
### C# Style Guidelines
- $\color{#4682B4}{\textsf{Formatting:}}$ use Visual Studio formatter;
- $\color{#4682B4}{\textsf{Error Handling:}}$
  * $\color{#4682B4}{\textsf{Exceptions:}}$ Use exceptions for error handling and avoid returning error codes if possible.
  * $\color{#4682B4}{\textsf{Custom Exceptions:}}$ Create custom exception classes if specific error information needs to be conveyed.
- $\color{#4682B4}{\textsf{Code Structure:}}$
  * $\color{#4682B4}{\textsf{File Organization:}}$ Organize code files logically (Related classes should be in the same namespace).
---
### C++ Style Guidelines
- $\color{#FFD700}{\textsf{Code Structure:}}$
  * $\color{#FFD700}{\textsf{File Organization:}}$ Organize code into files logically. Header files (`.h`) should contain declarations, while implementation files (`.cpp`) should contain definitions.
  * $\color{#FFD700}{\textsf{Include Guards:}}$ Use include guards (`#ifndef`, `#define`, `#endif`) or `#pragma once` to prevent multiple inclusions of header files.
---
### General Formatting Guidelines
- $\color{#00FA9A}{\textsf{Formatting:}}$
  * $\color{#00FA9A}{\textsf{Braces:}}$ Place opening braces `{` on the same line as the statement (except in cases where code is less readable) and closing braces `}` on their own line.
  * $\color{#00FA9A}{\textsf{Spaces:}}$ Use spaces around operators and after commas (e.g., `int result = a + b;`).
  * $\color{#00FA9A}{\textsf{Indentation:}}$ Use spaces for indentation always (4 space indentation).
  * Strictly enforce a $\color{#00FA9A}{\textsf{110 character}}$ line limit.
