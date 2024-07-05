## First homework

Implement the app which will show list and details of characters from the universe of Rick&Morty TV show.

Design of the app should be based on this Figma files

- [List](https://www.figma.com/file/0w76BZ8TviO2TQF84574Et/Rick-and-Morty-Test-Task-Design?node-id=0-1521&t=UQrfeRcqaj25xrKx-0)
- [Detail](https://www.figma.com/file/0w76BZ8TviO2TQF84574Et/Rick-and-Morty-Test-Task-Design?node-id=0-1041&t=UQrfeRcqaj25xrKx-0)
- [Search](https://www.figma.com/file/0w76BZ8TviO2TQF84574Et/Rick-and-Morty-Test-Task-Design?node-id=0-1317&t=UQrfeRcqaj25xrKx-0)

### List of characters screen

- BottomNavigationBar
    * BottomNavigationBar will do nothing, just UI
- ToolBar
    * Search icon will be clickable → Navigate to Search screen
- List of characters
    * Character will be clickable → Navigate to detail
    * Without star

### Search screen

- Arrow → navigate back
- Refresh list after each input change
- Character will be clickable → Navigate to detail (recommended to reuse the UI from List of characters screen)
- Search by name

### Detail screen

- Arrow → navigate back
- Pass characterId as parameter
- Full detail
- Star will be clickable and will change its state (No complex logic behind)
---

### General rules

- Implement the UI in Jetpack Compose
- For screen navigation use Navigation Component
- Use ViewModel and State
- Icons can be downloaded from Figma
- App will handle configuration change
- App should work in portrait and landscape
- Data should be defined statically within the app. You can use open sourced [API](https://rickandmortyapi.com/) for an inspiration
