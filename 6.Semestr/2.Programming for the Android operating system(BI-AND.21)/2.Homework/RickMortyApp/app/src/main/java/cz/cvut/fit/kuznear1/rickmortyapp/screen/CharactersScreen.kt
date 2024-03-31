package cz.cvut.fit.kuznear1.rickmortyapp.screen

import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyapp.BottomBar
import cz.cvut.fit.kuznear1.rickmortyapp.R
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters
import cz.cvut.fit.kuznear1.rickmortyapp.model.Character
import cz.cvut.fit.kuznear1.rickmortyapp.Screens

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun CharactersScreen(navController: NavController) {
    Scaffold(
        topBar = {
            CenterAlignedTopAppBar(
                title = { Text("Characters") })
        },
        bottomBar = { BottomBar() }
    ) {
        LazyColumn(modifier = Modifier.padding(it)) {
            items(characters) { character ->
                CharacterCard(character, navController)
            }
        }
    }
}


@Composable
fun CharacterCard(
    character: Character,
    navController: NavController,
) {
    Card(modifier = Modifier.padding(4.dp)) {
        CharacterItem(character) {
            navController.navigate(Screens.DetailScreen.route + "/${character.id}")
        }
    }
}


@Composable
fun CharacterItem(character: Character, onCharacterClick: () -> Unit) {
    Row(
        modifier = Modifier.fillMaxWidth().padding(8.dp).clickable { onCharacterClick() },
        horizontalArrangement = Arrangement.Start,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Box(
            modifier = Modifier
                .width(44.dp)
                .height(44.dp)
                .padding(0.dp) // Padding or gap
                .background(Color.Transparent) // Opacity
        ) {
            Image(
                painter = painterResource (id = character.icon),
                contentDescription = "ProfileIcon",
                contentScale = ContentScale.Crop,
                modifier = Modifier
                    .fillMaxSize()
            )
        }
        Spacer(modifier = Modifier.size(8.dp))

        Column() {
            Text(
                text = character.name,
                fontSize = 20.sp,
                fontWeight = FontWeight.Bold,
            )
            Text(
                text = character.status,
                fontSize = 14.sp,
            )
        }
    }
}

@Composable
fun Title(text: String) {
    Text(
        text = text,
        fontSize = 30.sp
    )
}