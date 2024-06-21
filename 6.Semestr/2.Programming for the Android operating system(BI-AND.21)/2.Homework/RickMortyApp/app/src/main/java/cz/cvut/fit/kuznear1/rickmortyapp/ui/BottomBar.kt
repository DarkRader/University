package cz.cvut.fit.kuznear1.rickmortyapp.ui

import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Face
import androidx.compose.material.icons.filled.Star
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.compose.material3.NavigationBarItem
import androidx.compose.ui.res.stringResource
import androidx.compose.material3.Text
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyapp.R
import cz.cvut.fit.kuznear1.rickmortyapp.Screens

@Composable
fun BottomBar(navController: NavController) {
    BottomAppBar(

    ) {
        NavigationBarItem(selected = true, onClick = {
            navController.navigate(Screens.CharactersScreen.route)
        },
            icon = {
                Icon(Icons.Default.Face,
                    contentDescription = null)
            },
            label = { Text(text = "Character") }
            )
        NavigationBarItem(selected = false, onClick = {
            navController.navigate(Screens.FavouriteScreen.route)
        },
            icon = {
                Icon(Icons.Default.Star,
                    contentDescription = null)
            },
            label = { Text(stringResource(R.string.favorite)) }
        )
    }
}