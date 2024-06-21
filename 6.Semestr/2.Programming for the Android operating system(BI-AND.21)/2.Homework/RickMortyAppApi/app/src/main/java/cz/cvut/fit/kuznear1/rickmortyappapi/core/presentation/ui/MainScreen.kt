package cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.RowScope
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.navigation.compose.currentBackStackEntryAsState
import androidx.navigation.compose.rememberNavController
import cz.cvut.fit.kuznear1.rickmortyappapi.R

@Composable
fun MainScreen() {
    Column {
        val navController = rememberNavController()

        Navigation(navController = navController, modifier = Modifier.weight(1f))

        val currentEntry by navController.currentBackStackEntryAsState()
        val currentEntryRoute = currentEntry?.destination?.route
        val shouldShowBottomNavigation = currentEntryRoute?.let(::hasBottomNavigation) ?: false

        if(shouldShowBottomNavigation) {
            BottomAppBar(containerColor = MaterialTheme.colorScheme.secondaryContainer) {
                NavigationBarItem(
                    painter = painterResource(id = R.drawable.ic_characters),
                    name = stringResource(id = R.string.characters),
                    selected = currentEntryRoute == Screens.CharactersScreen.route,
                    onClick = {
                        navController.popBackStack(Screens.CharactersScreen.route, inclusive = false)
                    }
                )

                NavigationBarItem(
                    painter = painterResource(id = R.drawable.ic_favorites_filled),
                    name = stringResource(id = R.string.favorites),
                    selected = currentEntryRoute == Screens.FavouriteScreen.route,
                    onClick = {
                        navController.navigate(Screens.FavouriteScreen.route)
                    }
                )
            }
        }
    }
}

private fun hasBottomNavigation(route: String): Boolean {
    return route in listOf(
        Screens.CharactersScreen.route,
        Screens.FavouriteScreen.route,
    )
}

@Composable
private fun RowScope.NavigationBarItem(
    painter: Painter,
    name: String,
    selected: Boolean,
    onClick: () -> Unit
) {
    val contentColor = if (selected) {
        MaterialTheme.colorScheme.primary
    } else {
        MaterialTheme.colorScheme.onTertiary
    }

    NavigationBarItem(
        selected = selected,
        onClick = onClick,
        icon = {
            Icon(painter = painter, contentDescription = null, tint = contentColor)

        },
        label = {
            Text(text = name, style = MaterialTheme.typography.labelMedium, color = contentColor)
        }
    )
}