package cz.cvut.fit.kuznear1.rickmortyapp.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyapp.Screens
import cz.cvut.fit.kuznear1.rickmortyapp.model.Character
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters
import cz.cvut.fit.kuznear1.rickmortyapp.ui.BottomBar

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun FavouriteScreen(navController: NavController) {
    val filteredCharacters = remember { mutableStateOf(characters.filter {
        it.favourite
    }) }

    Scaffold(
        topBar = {
            Surface(color = Color.White) {
                TopAppBar(
                    title = {
                        Title("Favourite")
                    },
                )
            }
        },
        bottomBar = { BottomBar(navController) }
    ) { innerPadding ->
        LazyColumn(modifier = Modifier.padding(innerPadding).background(Color.White)) {
            items(filteredCharacters.value) { character ->
                FavouriteCard(character, navController)
            }
        }
    }
}

@Composable
fun FavouriteCard(
    character: Character,
    navController: NavController,
) {
    Card(modifier = Modifier.padding(4.dp),
        colors = CardDefaults.cardColors(
            containerColor = Color(0xFFFFFFFF)
        )) {
        CharacterItem(character) {
            navController.navigate(Screens.DetailScreen.route + "/${character.id}")
        }
    }
}