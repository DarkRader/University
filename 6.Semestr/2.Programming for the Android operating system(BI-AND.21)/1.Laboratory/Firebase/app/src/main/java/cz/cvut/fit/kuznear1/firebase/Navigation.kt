package cz.cvut.fit.kuznear1.firebase

import androidx.compose.runtime.Composable
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import cz.cvut.fit.kuznear1.firebase.features.home.presentation.HomeScreen
import cz.cvut.fit.kuznear1.firebase.features.notes.presentation.NotesScreen
import cz.cvut.fit.kuznear1.firebase.features.profile.presentation.ProfileScreen

sealed class Screens(val route: String) {

    data object HomeScreen : Screens("home")

    data object NotesScreen : Screens("notes")

    data object ProfileScreen : Screens("profile")
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
