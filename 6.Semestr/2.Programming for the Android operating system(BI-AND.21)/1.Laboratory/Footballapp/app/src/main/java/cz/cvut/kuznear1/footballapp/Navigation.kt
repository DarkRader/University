package cz.cvut.kuznear1.footballapp

import androidx.compose.runtime.Composable
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import cz.cvut.kuznear1.footballapp.screen.DetailScreen
import cz.cvut.kuznear1.footballapp.screen.MatchScreen
import cz.cvut.kuznear1.footballapp.screen.TeamsScreen

@Composable
fun Navigation() {
    val navController = rememberNavController()

    NavHost(navController = navController, startDestination = Screens.MatchScreen.route) {
        composable(route = Screens.MatchScreen.route) {
            MatchScreen(navController = navController)
        }
        composable(route = Screens.TeamsScreen.route) {
            TeamsScreen(navController = navController)
        }
        composable(route = Screens.DetailScreen.route + "/{id}",
            arguments = listOf(
                navArgument(name = "id") {
                    type =  NavType.IntType
                }
            )) { entry ->
            DetailScreen(navController = navController, id = entry.arguments?.getInt("id"))
        }
    }
}

sealed class Screens(val route: String) {
    data object MatchScreen: Screens("match")
    data object TeamsScreen: Screens("teams")
    data object DetailScreen: Screens("detail")
}
