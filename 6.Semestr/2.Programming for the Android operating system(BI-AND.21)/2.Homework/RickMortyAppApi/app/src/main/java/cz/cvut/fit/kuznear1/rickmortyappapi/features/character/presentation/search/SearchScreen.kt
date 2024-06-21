package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.search

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Close
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.rickmortyappapi.R
import cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.character.CharacterItem
import org.koin.androidx.compose.koinViewModel


@Composable
fun SearchScreen(
    navController: NavController,
    viewModel: SearchViewModel = koinViewModel(),
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    SearchScreenContent(
        screenState = screenState,
        onNavigateBackClick = { navController.popBackStack() },
        onQueryChange = viewModel::searchCharacters,
        onClearClick = viewModel::clearText,
        onCharacterClick = { character ->
            navController.navigate(Screens.DetailScreen.route + "/${character.id}")
        },
    )
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun SearchScreenContent(
    screenState: SearchScreenState,
    onNavigateBackClick: () -> Unit,
    onQueryChange: (String) -> Unit,
    onClearClick: () -> Unit,
    onCharacterClick: (Character) -> Unit,
) {
    Scaffold(
        topBar = {
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
                    SearchTopBarContent(
                        query = screenState.query,
                        onQueryChange = onQueryChange,
                        onClearClick = onClearClick,
                    )
                },
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primaryContainer
                )
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,
    ) {
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(it)
        ) {
            items(screenState.characters) { character ->
                CharacterItem(
                    character = character,
                    modifier = Modifier
                        .fillMaxWidth()
                        .clickable { onCharacterClick(character) }
                        .padding(horizontal = 16.dp, vertical = 12.dp)
                )
            }
        }
    }
}

@Composable
private fun SearchTopBarContent(
    query: String,
    onQueryChange: (String) -> Unit,
    onClearClick: () -> Unit,
) {
    var text by remember { mutableStateOf(query) }

    TextField(
        modifier = Modifier
            .fillMaxWidth()
            .padding(top = 2.dp),
        value = text,
        onValueChange = { newText ->
            text = newText
        },
        placeholder = {
            Text(
                text = stringResource(R.string.search_characters),
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSecondary,
            )
        },
        colors = TextFieldDefaults.colors(
            focusedContainerColor = Color.Transparent,
            unfocusedContainerColor = Color.Transparent,
            focusedIndicatorColor = Color.Transparent,
            unfocusedIndicatorColor = Color.Transparent,
            focusedTextColor = MaterialTheme.colorScheme.onPrimary,
        ),
        textStyle = MaterialTheme.typography.bodyMedium,
        trailingIcon = {
            if(query.isNotEmpty()) {
                IconButton(onClick = {
                    onClearClick()
                    text = ""
                }) {
                    Icon(
                        imageVector = Icons.Filled.Close,
                        contentDescription = stringResource(id = R.string.clear),
                        tint = MaterialTheme.colorScheme.onSecondary,
                    )
                }
            }
        },
        keyboardOptions = KeyboardOptions.Default.copy(
            imeAction = ImeAction.Done
        ),
        keyboardActions = KeyboardActions(
            onDone = {
                onQueryChange(text)
            }
        )
    )
}