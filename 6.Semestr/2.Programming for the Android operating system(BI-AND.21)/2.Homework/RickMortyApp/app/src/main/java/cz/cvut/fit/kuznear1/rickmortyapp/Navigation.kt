package cz.cvut.fit.kuznear1.rickmortyapp

import androidx.compose.runtime.Composable
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import cz.cvut.fit.kuznear1.rickmortyapp.screen.CharactersScreen
import cz.cvut.fit.kuznear1.rickmortyapp.screen.DetailScreen
import cz.cvut.fit.kuznear1.rickmortyapp.screen.SearchScreen
import cz.cvut.fit.kuznear1.rickmortyapp.screen.FavouriteScreen

@Composable
fun Navigation() {
    val navController = rememberNavController()
    
    NavHost(navController = navController, startDestination = Screens.CharactersScreen.route) {
        composable(route = Screens.CharactersScreen.route) {
            CharactersScreen(navController = navController)
        }
        composable(route = Screens.FavouriteScreen.route) {
            FavouriteScreen(navController = navController)
        }
        composable(route = Screens.SearchScreen.route) {
            SearchScreen(navController = navController)
        }
        composable(route = Screens.DetailScreen.route + "/{id}",
            arguments = listOf(
                navArgument(name = "id") {
                    type = NavType.IntType
                }
            )) {entry ->
            DetailScreen(navController = navController, id = entry.arguments?.getInt("id"))
        }
    }

}

sealed class Screens(val route: String) {
    data object CharactersScreen: Screens("characters")
    data object SearchScreen: Screens("search")
    data object DetailScreen: Screens("detail")
    data object FavouriteScreen: Screens("favourite")
}