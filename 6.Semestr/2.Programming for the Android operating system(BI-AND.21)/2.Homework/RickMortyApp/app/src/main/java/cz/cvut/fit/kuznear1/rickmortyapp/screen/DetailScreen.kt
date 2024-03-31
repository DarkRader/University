package cz.cvut.fit.kuznear1.rickmortyapp.screen

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.IconButton
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.Icon
import androidx.compose.runtime.Composable
import androidx.navigation.NavController
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import cz.cvut.fit.kuznear1.rickmortyapp.R
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun DetailScreen(navController: NavController, id: Int?) {
    val character = characters.find { it.id == id }
    character?.let { 
        Scaffold(
            topBar = {
                CenterAlignedTopAppBar(
                    title = { Text(character.name) },
                    navigationIcon = {
                        IconButton(onClick = { navController.navigateUp() }) {
                            Icon(
                                imageVector = Icons.Default.ArrowBack,
                                contentDescription = null
                            )
                        }
                    }
                )
            }
        ) {
            Column(
                modifier = Modifier
                    .padding(it)
                    .fillMaxSize()
            ) {
//                AsyncImage(
//                    modifier = Modifier
//                        .size(120.dp)
//                        .padding(8.dp)
//                        .clip(CircleShape),
//                    model = painterResource (id = R.drawable.rick),
//                    contentDescription = null,
//                )
                Spacer(modifier = Modifier.height(60.dp))
                Title(text = stringResource(R.string.character_name, character.name))
            }
        }
    }
}