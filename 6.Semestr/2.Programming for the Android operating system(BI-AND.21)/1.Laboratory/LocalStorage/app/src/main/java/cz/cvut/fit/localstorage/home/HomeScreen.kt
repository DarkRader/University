package cz.cvut.fit.localstorage.home

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import cz.cvut.fit.localstorage.Screens

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun HomeScreen(
    navController: NavController,
) {
    Scaffold(
        topBar = {
            TopAppBar(title = { Text("Welcome!") })
        },
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .padding(12.dp)
                .fillMaxSize(),
        ) {
            Button(
                onClick = { navController.navigate(Screens.NotesScreen.route) },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text("Notes")
            }

            Button(
                onClick = { navController.navigate(Screens.ProfileScreen.route) },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text("Profile")
            }
        }
    }
}
