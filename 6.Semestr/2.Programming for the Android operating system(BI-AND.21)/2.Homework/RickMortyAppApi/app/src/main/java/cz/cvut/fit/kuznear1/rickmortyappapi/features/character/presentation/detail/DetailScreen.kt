package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.detail

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
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import coil.compose.AsyncImage
import cz.cvut.fit.kuznear1.rickmortyappapi.R
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import org.koin.androidx.compose.koinViewModel

@Composable
fun DetailScreen(
    navController: NavController,
    viewModel: DetailViewModel = koinViewModel(),
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    DetailScreen(
        screenState = screenState,
        onFavouriteClick = viewModel::onFavouriteClick,
        onNavigateBackClick = { navController.popBackStack() },
    )
}

@Composable
private fun DetailScreen(
    screenState: DetailScreenState,
    onFavouriteClick: () -> Unit,
    onNavigateBackClick: () -> Unit,
) {
    screenState.character?.let {character ->
        Scaffold(
            topBar = {
                DetailTopBar(
                    character = character,
                    onNavigateBackClick = onNavigateBackClick,
                    onFavoriteClick = onFavouriteClick,
                )
            },
            containerColor = MaterialTheme.colorScheme.primaryContainer,
        ) {
            Box(modifier = Modifier.padding(it)) {
                CharacterDetail(character)
            }
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
private fun DetailTopBar(
    character: Character,
    onNavigateBackClick: () -> Unit,
    onFavoriteClick: () -> Unit,
) {
    TopAppBar(
        navigationIcon = {
            IconButton(onClick = onNavigateBackClick) {
                Icon(
                    painter = painterResource(id = R.drawable.ic_back),
                    contentDescription = stringResource(id = R.string.back),
                    tint = MaterialTheme.colorScheme.onPrimary,
                )
            }
        },
        title = {
            Text(
                text = character.name,
                style = MaterialTheme.typography.headlineMedium,
                color = MaterialTheme.colorScheme.onPrimary
            )
        },
        actions = {
            IconButton(onClick = onFavoriteClick) {
                Icon(
                    painter = if (character.favourite) {
                        painterResource(id = R.drawable.ic_favorites_filled)
                    } else {
                        painterResource(id = R.drawable.ic_favorites)
                    },
                    tint = if (character.favourite) {
                        MaterialTheme.colorScheme.primary
                    } else {
                        MaterialTheme.colorScheme.onPrimary
                    },
                    contentDescription = stringResource(id = R.string.favorite),
                )
            }
        },
        colors = TopAppBarDefaults.topAppBarColors(
            containerColor = MaterialTheme.colorScheme.primaryContainer
        )
    )
}

@Composable
private fun CharacterDetail(character: Character) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState()),
    ) {
        Card(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            elevation = CardDefaults.cardElevation(2.dp),
            shape = RoundedCornerShape(16.dp),
            colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer)
        ) {
            CharacterCardHeader(character)
            Spacer(modifier = Modifier.height(14.dp))
            HorizontalDivider(
                color = MaterialTheme.colorScheme.outlineVariant,
                modifier = Modifier.fillMaxWidth(),
                thickness = 1.dp
            )
            Spacer(modifier = Modifier.height(16.dp))
            CharacterCardDetails(character)
            Spacer(modifier = Modifier.height(24.dp))
        }
    }
}

@Composable
private fun CharacterCardHeader(character: Character) {
    Row(modifier = Modifier.padding(all = 16.dp)) {
        AsyncImage(
            model = character.imageUrl,
            modifier = Modifier
                .clip(RoundedCornerShape(8.dp))
                .size(140.dp),
            contentDescription = "Image",
        )
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(horizontal = 16.dp),
        ) {
            Text(
                text = stringResource(R.string.name),
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSecondary
            )
            Spacer(modifier = Modifier.height(14.dp))
            Text(
                text = character.name,
                style = MaterialTheme.typography.headlineMedium,
                color = MaterialTheme.colorScheme.onPrimary,
            )
        }
    }
}

@Composable
private fun CharacterCardDetails(character: Character) {
    Column(
        modifier = Modifier
            .fillMaxWidth(fraction = 2 / 3f)
            .padding(horizontal = 16.dp),
        verticalArrangement = Arrangement.spacedBy(14.dp),
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
private fun CharacterParameters(characterParam: String?, text: String) {
    Column {
        Text(
            text = text,
            style = MaterialTheme.typography.bodySmall,
            color = MaterialTheme.colorScheme.onSecondary,
        )
        Text(
            text = characterParam?.takeUnless { it.isBlank() } ?: "-",
            style = MaterialTheme.typography.headlineSmall,
            color = MaterialTheme.colorScheme.onPrimary,
        )
    }
}
