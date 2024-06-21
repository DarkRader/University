package cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui

import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.detail.DetailScreen
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.favorite.FavouriteScreen
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.list.CharactersScreen
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.search.SearchScreen

@Composable
fun Navigation(
    navController: NavHostController,
    modifier: Modifier = Modifier
) {
    NavHost(
        navController = navController,
        startDestination = Screens.CharactersScreen.route,
        modifier = modifier,
        ) {
        composable(route = Screens.CharactersScreen.route) {
            CharactersScreen(navController = navController)
        }
        composable(route = Screens.FavouriteScreen.route) {
            FavouriteScreen(navController = navController)
        }
        composable(route = Screens.SearchScreen.route) {
            SearchScreen(navController = navController)
        }
        composable(
            route = Screens.DetailScreen.route + "/{${Screens.DetailScreen.ID_KEY}}",
            arguments = listOf(
                navArgument(name = Screens.DetailScreen.ID_KEY) {
                    type = NavType.LongType
                },
            ),
        ) {
            DetailScreen(navController = navController)
        }
    }
}

