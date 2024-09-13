# <span style="color:blue">Ningin</span>

## <span style="color:green">Code Style Guidelines</span>

### <span style="color:orange">Function Naming Conventions</span>

- **1.** <span style="color:purple">Use PascalCase</span> for all function names.
- **2.** <span style="color:purple">Verb-Noun</span> Functions often perform actions, so it’s common to use a verb followed by a noun to describe what the function does.
- **3.** <span style="color:purple">Descriptive but Concise</span> Function names should be descriptive enough to understand what they do but not overly verbose.
- **4.** <span style="color:purple">Use Domain-Specific Terms</span> If a function is related to a particular domain (e.g. physics), using terms from that domain can help.
- **5.** <span style="color:purple">Action-Oriented Naming</span> Functions should represent actions, so using strong action verbs is ideal.
- **6.** <span style="color:purple">Boolean-returning functions</span> For functions that return a boolean, the name should reflect a yes/no question. (e.g., `IsVisible()`, `HasCollision()`).
- **7.** <span style="color:purple">Accessor functions</span> should use `Get` and `Set` prefixes for retrieving and modifying properties (e.g., `GetScore()`, `SetVelocity()`).

* **8.** <span style="color:blue">Follow the Command-Query Separation principle:</span>
  * **Commands**: Functions that perform actions (usually without returning a value) - Example: `MovePlayer()`
  * **Queries**: Functions that return values or answer questions. - Example: `GetScore()`, `IsGameOver()`
- **9.** <span style="color:purple">Avoid abbreviations</span>, use full descriptive names (e.g., `CalculateTotal()` instead of `CalcTot()`).

---

### <span style="color:orange">Additional Naming Conventions</span>

- **Class names** should also follow PascalCase (**Structs** and **Enums** too).
- **Constants** should be written in CAMEL_CASE format.
- **Variables:** 
  * **1.** <span style="color:purple">Should be written in camelCase format.</span>                                                                                 
  * **2.** <span style="color:purple">Ascribe a name to each variable that clearly describes its purpose.</span>
  * **3.** <span style="color:purple">A single variable can’t be assigned various values in multiple contexts.</span>
- **File names** should match **class/struct/enum names** (e.g. `Vector2.h` for a `Vector2` class).

---

### <span style="color:orange">General Guidelines</span>
- Maintain <span style="color:purple">consistency</span> across related functions (e.g. `AddItem()`, `RemoveItem()`, and `ClearItems()`).
- Strictly enforce a <span style="color:purple">110 character</span> line limit.
- Avoid <span style="color:purple">Deep Nesting</span>. To maintain readability, aim for a no more than 3 levels of nesting.
- Avoid <span style="color:purple">Multi-Task functions:</span> a single function should carry out a single task.
- Use the <span style="color:purple">DRY (Don’t Repeat Yourself)</span> principle, the same piece of code should not be repeated.
- Add <span style="color:purple">Comments</span> for explaining the logic, functionality, or the purpose of specific sections.
- Divide the code into smaller self-contained modules and functions to enhance, reusability and maintainability.
- Use <span style="color:purple">spaces</span> for indentation always (4 space indentation)
