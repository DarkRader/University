package cz.cvut.fit.kuznear1.rickmortyapp

import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Favorite
import androidx.compose.material.icons.filled.Home
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.material3.NavigationBarItem
import androidx.compose.ui.res.stringResource
import androidx.compose.material3.Text

@Preview
@Composable
fun BottomBar() {
    BottomAppBar() {
        NavigationBarItem(selected = true, onClick = {},
            icon = {
                Icon(Icons.Default.Home,
                    contentDescription = null)
            },
            label = { Text(stringResource(R.string.home)) }
            )
        NavigationBarItem(selected = false, onClick = {},
            icon = {
                Icon(Icons.Default.Favorite,
                    contentDescription = null)
            },
            label = { Text(stringResource(R.string.favorite)) }
        )
    }
}