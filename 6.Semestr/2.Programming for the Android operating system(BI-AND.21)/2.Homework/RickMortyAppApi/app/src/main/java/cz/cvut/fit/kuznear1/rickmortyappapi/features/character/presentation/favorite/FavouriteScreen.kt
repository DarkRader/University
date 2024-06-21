package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.favorite

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyappapi.R
import cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.list.CharacterCard
import org.koin.androidx.compose.koinViewModel

@Composable
fun FavouriteScreen(
    navController: NavController,
    viewModel: FavouriteViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) {
        viewModel.updateFavouriteCharacters()
    }

    FavouriteScreenContent(
        screenState = screenState,
        onCharacterClick = { character ->
            navController.navigate(Screens.DetailScreen.route + "/${character.id}")
        },
    )
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun FavouriteScreenContent(
    screenState: FavouriteScreenState,
    onCharacterClick: (Character) -> Unit,
) {
    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Text(
                        text = stringResource(id = R.string.favorites),
                        style = MaterialTheme.typography.headlineMedium,
                        color = MaterialTheme.colorScheme.onPrimary
                    )
                },
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primaryContainer
                )
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,
    ) { innerPadding ->
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
            contentPadding = PaddingValues(8.dp),
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            items(screenState.characters, key = { it.id }) { character ->
                CharacterCard(
                    character = character,
                    onClick = { onCharacterClick(character) }
                )
            }
        }
    }
}