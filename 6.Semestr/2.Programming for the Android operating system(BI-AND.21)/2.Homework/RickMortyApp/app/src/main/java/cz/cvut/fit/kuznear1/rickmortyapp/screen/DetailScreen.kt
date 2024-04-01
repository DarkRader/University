package cz.cvut.fit.kuznear1.rickmortyapp.screen

import android.util.Log
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material.icons.filled.Favorite
import androidx.compose.material.icons.filled.Search
import androidx.compose.material.icons.filled.Star
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.Divider
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.IconButton
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.Icon
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.navigation.NavController
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.compose.rememberNavController
import coil.compose.AsyncImage
import cz.cvut.fit.kuznear1.rickmortyapp.LoadingViewModel
import cz.cvut.fit.kuznear1.rickmortyapp.R
import cz.cvut.fit.kuznear1.rickmortyapp.ScreenState
import cz.cvut.fit.kuznear1.rickmortyapp.model.Character
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun DetailScreen(navController: NavController, id: Int?) {
    val character = characters.find { it.id == id }
    val viewModel: LoadingViewModel = LoadingViewModel()
    val screenState by viewModel.screenState.collectAsState()

    character?.let {
        Scaffold(
            topBar = {
                if (screenState != ScreenState.Loading) {
                    TopAppBar(
                        title = { Title(text = character.name) },
                        navigationIcon = {
                            IconButton(onClick = { navController.navigateUp() }) {
                                Icon(
                                    imageVector = Icons.Default.ArrowBack,
                                    contentDescription = null
                                )
                            }
                        },
                        actions = {
                            IconButton(
                                onClick = {
                                    viewModel.addFavourite(character)
                                },
                                modifier = Modifier.padding(end = 16.dp)
                            ) {
                                Icon(
                                    Icons.Default.Star,
                                    contentDescription = "Favourite",
                                    tint = if (character.favourite) Color.Blue else Color.Black,
                                    modifier = Modifier.size(36.dp)
                                )
                            }
                        },
                    )
                }
            }
        ) {
            when (screenState) {
                ScreenState.Loading -> LoadingScreen(modifier = Modifier.padding(it))
                ScreenState.Default ->  {
                    Column(
                        modifier = Modifier
                            .padding(it)
                            .fillMaxSize()
                            .background(Color.LightGray)
                            .verticalScroll(rememberScrollState())
                    ) {
                        CharacterDetail(character = character)
                    }
                }
            }
        }
    }
}

@Composable
fun CharacterDetail(character: Character) {

    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(8.dp),
        horizontalArrangement = Arrangement.Start,
    ) {
        Image(
            painter = painterResource (id = character.icon),
            contentDescription = "ProfileIcon",
            contentScale = ContentScale.Crop,
            modifier = Modifier
                .size(140.dp)
                .clip(RoundedCornerShape(8.dp))
        )
        Spacer(modifier = Modifier.size(8.dp))

        Column(modifier = Modifier.padding(6.dp)) {
            Text(
                text = "Name",
                fontSize = 18.sp,
                fontWeight = FontWeight.Normal,
                color = Color.Gray,
                lineHeight = 20.sp,
                textAlign = TextAlign.Left,
            )
            Text(
                text = character.name,
                fontSize = 22.sp,
                fontWeight = FontWeight.Bold,
                lineHeight = 24.2.sp
            )
        }
    }
    Divider(color = Color.Gray, thickness = 1.dp)
    Spacer(modifier = Modifier.size(10.dp))
    Column(
        modifier = Modifier
            .padding(16.dp)
            .fillMaxSize()
    ) {
        CharacterParameters(character.status, "Status")
        CharacterParameters(character.species, "Species")
        CharacterParameters(character.type, "Type")
        CharacterParameters(character.gender, "Gender")
        CharacterParameters(character.origin, "Origin")
        CharacterParameters(character.location, "Location")
    }
}
@Composable
fun CharacterParameters(characterParam: String, text: String) {
    Text(
        text = text,
        fontSize = 16.sp,
        fontWeight = FontWeight.Normal,
        lineHeight = 20.sp,
        textAlign = TextAlign.Left,
        color = Color.Gray
    )
    Text(
        text = characterParam,
        fontSize = 18.sp,
        fontWeight = FontWeight.Bold,
        lineHeight = 24.2.sp
    )
    Spacer(modifier = Modifier.size(20.dp))
}

@Preview
@Composable
fun DetailScreen() {
    val navController = rememberNavController()
    DetailScreen(navController, 1)
}