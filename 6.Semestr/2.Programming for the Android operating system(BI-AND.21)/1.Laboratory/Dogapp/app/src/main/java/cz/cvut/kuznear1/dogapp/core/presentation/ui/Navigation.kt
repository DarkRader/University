package cz.cvut.kuznear1.dogapp.core.presentation.ui

import androidx.annotation.StringRes
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.material.icons.filled.Person
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.res.stringResource
import androidx.navigation.NavDestination.Companion.hierarchy
import androidx.navigation.NavGraph.Companion.findStartDestination
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.currentBackStackEntryAsState
import androidx.navigation.compose.rememberNavController
import androidx.navigation.navArgument
import cz.cvut.kuznear1.dogapp.R
import cz.cvut.kuznear1.dogapp.features.breed.presentation.detail.BreedDetailScreen
import cz.cvut.kuznear1.dogapp.features.breed.presentation.list.BreedsScreen
import cz.cvut.kuznear1.dogapp.features.fact.presentation.FactsScreen

sealed class Screens(val route: String) {

    sealed class TopLevel(route: String) : Screens(route) {

        @get:StringRes
        abstract val title: Int

        abstract val icon: ImageVector

        data object Breeds : TopLevel("breeds") {

            override val title = R.string.bottom_nav_title_breeds

            override val icon = Icons.Filled.Person
        }

        data object Facts : TopLevel("facts") {

            override val title = R.string.bottom_nav_title_facts

            override val icon = Icons.Filled.Info
        }

        companion object {

            val all get() = listOf(Facts, Breeds)
        }
    }

    class BreedDetail(breedId: String) : Screens("breeds/$breedId") {

        companion object {

            const val ID = "id"
        }
    }
}

@Composable
fun Navigation() {
    val navController = rememberNavController()
    Scaffold(
        bottomBar = {
            BottomAppBar {
                val navBackStackEntry by navController.currentBackStackEntryAsState()
                val currentDestination = navBackStackEntry?.destination
                Screens.TopLevel.all.forEach { screen ->
                    NavigationBarItem(
                        icon = { Icon(screen.icon, contentDescription = null) },
                        label = { Text(stringResource(screen.title)) },
                        selected = currentDestination?.hierarchy?.any { it.route == screen.route } == true,
                        onClick = {
                            navController.navigate(screen.route) {
                                popUpTo(navController.graph.findStartDestination().id)
                                launchSingleTop = true
                            }
                        }
                    )
                }
            }
        }
    ) { innerPadding ->
        NavHost(
            navController = navController,
            startDestination = Screens.TopLevel.Facts.route,
            modifier = Modifier.padding(innerPadding),
        ) {
            composable(route = Screens.TopLevel.Breeds.route) {
                BreedsScreen(navigateToBreedDetail = {
                    navController.navigate(Screens.BreedDetail(it).route)
                })
            }

            composable(
                route = Screens.BreedDetail("{${Screens.BreedDetail.ID}}").route,
                arguments = listOf(navArgument(Screens.BreedDetail.ID) { type = NavType.StringType }),
            ) {
                BreedDetailScreen(navigateUp = { navController.navigateUp() })
            }

            composable(route = Screens.TopLevel.Facts.route) {
                FactsScreen()
            }
        }
    }
}