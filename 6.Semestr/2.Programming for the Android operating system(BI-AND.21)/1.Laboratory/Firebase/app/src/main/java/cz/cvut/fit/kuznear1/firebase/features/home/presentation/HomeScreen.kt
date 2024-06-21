package cz.cvut.fit.kuznear1.firebase.features.home.presentation

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
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.firebase.R
import cz.cvut.fit.kuznear1.firebase.Screens

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun HomeScreen(
    navController: NavController,
) {
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text(stringResource(id = R.string.welcome)) }
            )
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
                Text(stringResource(id = R.string.notes))
            }

            Button(
                onClick = { navController.navigate(Screens.ProfileScreen.route) },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text(stringResource(id = R.string.profile))
            }
        }
    }
}
