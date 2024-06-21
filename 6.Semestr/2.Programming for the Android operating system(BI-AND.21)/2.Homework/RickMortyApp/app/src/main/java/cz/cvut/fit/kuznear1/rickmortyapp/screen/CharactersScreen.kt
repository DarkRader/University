package cz.cvut.fit.kuznear1.rickmortyapp.screen

import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Search
import androidx.compose.material.icons.filled.Star
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.navigation.compose.rememberNavController
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyapp.ui.BottomBar
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters
import cz.cvut.fit.kuznear1.rickmortyapp.model.Character
import cz.cvut.fit.kuznear1.rickmortyapp.Screens

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun CharactersScreen(navController: NavController) {
    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Title("Characters")
                },
                actions = {
                    IconButton(
                        onClick = {
                            navController.navigate(Screens.SearchScreen.route)
                        },
                        modifier = Modifier.padding(end = 16.dp)
                    ) {
                        Icon(
                            Icons.Default.Search,
                            contentDescription = "Search",
                            modifier = Modifier.size(36.dp)
                        )
                    }
                },
            )
        },
        bottomBar = { BottomBar(navController) }
    ) { innerPadding ->
        LazyColumn(modifier = Modifier.padding(innerPadding).background(Color.White)) {
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
        Card(modifier = Modifier.padding(4.dp),
            colors = CardDefaults.cardColors(
                containerColor = Color(0xFFFFFFFF)
            )) {
            CharacterItem(character) {
                navController.navigate(Screens.DetailScreen.route + "/${character.id}")
            }
        }
}


@Composable
fun CharacterItem(character: Character, onCharacterClick: () -> Unit) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp)
            .clickable { onCharacterClick() },
        horizontalArrangement = Arrangement.Start,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Image(
            painter = painterResource (id = character.icon),
            contentDescription = "ProfileIcon",
            contentScale = ContentScale.Crop,
            modifier = Modifier.size(44.dp).clip(RoundedCornerShape(8.dp))
        )
        Spacer(modifier = Modifier.size(8.dp))

        Column {
            Row(
                horizontalArrangement = Arrangement.Start,
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(
                    text = character.name,
                    fontSize = 20.sp,
                    fontWeight = FontWeight.Bold,
                )
                Spacer(modifier = Modifier.size(10.dp))
                if(character.favourite) {
                    Icon(
                        Icons.Default.Star,
                        contentDescription = "Favourite",
                        modifier = Modifier.size(20.dp),
                        tint = Color.Blue
                    )
                }
            }
            Text(
                text = character.status,
                fontSize = 14.sp,
                fontWeight = FontWeight.Normal,
                color = Color.Gray
            )
        }
    }
}

@Composable
fun Title(text: String) {
    Text(
        text = text,
        textAlign = TextAlign.Start,
        fontSize = 25.sp,
        fontWeight = FontWeight.Bold
    )
}

@Preview
@Composable
fun CharactersScreenPreview() {
    val navController = rememberNavController()
    CharactersScreen(navController)
}