package cz.cvut.fit.kuznear1.rickmortyapp.ui

import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Face
import androidx.compose.material.icons.filled.Star
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.material3.NavigationBarItem
import androidx.compose.ui.res.stringResource
import androidx.compose.material3.Text
import cz.cvut.fit.kuznear1.rickmortyapp.R

@Preview
@Composable
fun BottomBar() {
    BottomAppBar(

    ) {
        NavigationBarItem(selected = true, onClick = {},
            icon = {
                Icon(Icons.Default.Face,
                    contentDescription = null)
            },
            label = { Text(text = "Character") }
            )
        NavigationBarItem(selected = false, onClick = {},
            icon = {
                Icon(Icons.Default.Star,
                    contentDescription = null)
            },
            label = { Text(stringResource(R.string.favorite)) }
        )
    }
}