package cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.RowScope
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material.icons.filled.DateRange
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.navigation.compose.rememberNavController
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.graphics.vector.rememberVectorPainter
import androidx.compose.ui.res.stringResource
import androidx.navigation.compose.currentBackStackEntryAsState
import cz.cvut.fit.kuznear1.bukreservationapp.R

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
                    painter = rememberVectorPainter(image = Icons.Default.DateRange),
                    name = stringResource(id = R.string.reservation),
                    selected = currentEntryRoute == Screens.ReservationScreen.route,
                    onClick = {
                        navController.popBackStack(Screens.ReservationScreen.route, inclusive = false)
                    }
                )

                NavigationBarItem(
                    painter = rememberVectorPainter(image = Icons.Default.AccountCircle),
                    name = stringResource(id = R.string.profile),
                    selected = currentEntryRoute == Screens.ProfileScreen.route,
                    onClick = {
                        navController.navigate(Screens.ProfileScreen.route)
                    }
                )
            }
        }
    }
}

private fun hasBottomNavigation(route: String): Boolean {
    return route in listOf(
        Screens.ReservationScreen.route,
        Screens.ProfileScreen.route,
    )
}

@Composable
private fun RowScope.NavigationBarItem(
    painter: Painter,
    name: String,
    selected: Boolean,
    onClick: () -> Unit
) {
    val iconColor = if (selected) {
        MaterialTheme.colorScheme.primary
    } else {
        MaterialTheme.colorScheme.onTertiary
    }

    NavigationBarItem(
        selected = selected,
        onClick = onClick,
        icon = {
            Icon(painter = painter, contentDescription = null, tint = iconColor)
        },
        label = {
            Text(text = name, style = MaterialTheme.typography.labelMedium, color = iconColor)
        }
    )
}