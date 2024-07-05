## Second homework

The second homework is based on the first one. You’ll extend the Rick & Morty application with the real data

- Use the REST [api](https://rickandmortyapi.com/documentation/#rest) to fetch the list of characters (only the first page). Use Retrofit + Coroutines
- Store this list to database using Room and display it in the UI (the data source for the list/detail is the database)
- On detail screen retrieve the data from the database, no need for additional api request (pass only the character id from the list). Return `Flow` of characters from the Room DAO. WARNING: If the character has not been downloaded before, no indication of data should be displayed or the character should be downloaded from the API.
- Use the recommended architecture shown on the lecture or from the official Google guidelines. Use dependency injection for injecting dependencies in constructors and optionally some DI framework (Koin, Dagger, Hilt). However, `Retrofit` and database instances must be singletons.
- Fetch the character images using any of the recommended image loading libraries (Coil, Picasso or Glide)
- Implement searching through a special API [endpoint](https://rickandmortyapi.com/documentation/#filter-characters)
  * Do not store results in the Database, display the API response directly (unless you really want to 😏)
- You can earn some extra points
  * Favorites - 5p
    - Store information which character is favorite to the database and display it in the UI of the characters list (as a star after the name), separate Favorites screen in the Bottom navigation and the star toggle in the Toolbar on the detail
- The homework will be checked through Gitlab Merge request and the deadline is 2. 5. 2024 23:59