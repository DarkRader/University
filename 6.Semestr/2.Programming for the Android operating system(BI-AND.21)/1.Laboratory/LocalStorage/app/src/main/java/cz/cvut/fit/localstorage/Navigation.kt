package cz.cvut.fit.localstorage

import androidx.compose.runtime.Composable
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import cz.cvut.fit.localstorage.home.HomeScreen
import cz.cvut.fit.localstorage.notes.NotesScreen
import cz.cvut.fit.localstorage.profile.ProfileScreen

sealed class Screens(val route: String) {

    object HomeScreen : Screens("home")

    object NotesScreen : Screens("notes")

    object ProfileScreen : Screens("profile")
}

@Composable
fun Navigation() {
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = Screens.HomeScreen.route,
    ) {
        composable(route = Screens.HomeScreen.route) {
            HomeScreen(navController)
        }

        composable(route = Screens.NotesScreen.route) {
            NotesScreen(navController)
        }

        composable(route = Screens.ProfileScreen.route) {
            ProfileScreen(navController)
        }
    }
}
