package cz.cvut.kuznear1.tweenapp.ui

import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Home
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.tooling.preview.Preview

@Preview
@Composable
fun BottomBar() {
    BottomAppBar {
        NavigationBarItem(selected = true, onClick = {},
            icon = {
                Icon(Icons.Default.Home, contentDescription = null)
            },
            label = { Text("Favourite") }
            )
    }
}