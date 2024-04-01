package cz.cvut.fit.kuznear1.rickmortyapp.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.foundation.text.BasicTextField
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.filled.Close
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.SolidColor
import androidx.compose.ui.platform.LocalSoftwareKeyboardController
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import androidx.navigation.compose.rememberNavController
import cz.cvut.fit.kuznear1.rickmortyapp.ui.BottomBar
import cz.cvut.fit.kuznear1.rickmortyapp.LoadingViewModel
import cz.cvut.fit.kuznear1.rickmortyapp.ScreenState
import cz.cvut.fit.kuznear1.rickmortyapp.model.characters

@Composable
fun SearchScreen(navController: NavController) {
    val filteredCharacters = remember { mutableStateOf(characters.filter {
        it.name.contains("Search characters")
    }) }
    val keyboardController = LocalSoftwareKeyboardController.current

    val viewModel: LoadingViewModel = LoadingViewModel()
    val screenState by viewModel.screenState.collectAsState()

    Scaffold(
        topBar = {
            SearchableTopAppBar(
                onSearch = { searchText ->
                    filteredCharacters.value = if (searchText.isEmpty()) {
                        emptyList()
                    } else {
                        characters.filter { it.name.contains(searchText, ignoreCase = true) }
                    }
                    keyboardController?.hide()
                },
                navController = navController,
                viewModel = viewModel
            )
        },
        bottomBar = { BottomBar() }
    ) { innerPadding ->
        when (screenState) {
            ScreenState.Loading -> LoadingScreen(modifier = Modifier.padding(innerPadding))
            ScreenState.Default -> {
                LazyColumn(
                    modifier = Modifier.padding(innerPadding).background(Color.LightGray)
                ) {
                    items(filteredCharacters.value) { character ->
                        CharacterCard(character, navController)
                    }
                }
            }
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun SearchableTopAppBar(onSearch: (String) -> Unit,
                        navController: NavController,
                        viewModel: LoadingViewModel,
) {
    val keyboardController = LocalSoftwareKeyboardController.current
    var searchText by rememberSaveable { mutableStateOf("") }
    var isHintDisplayed by remember { mutableStateOf(true) }

    TopAppBar(
        title = {
            Row(
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier.fillMaxWidth(),
            ) {
                BasicTextField(
                    value = searchText,
                    onValueChange = {
                        searchText = it
                        isHintDisplayed = it.isEmpty()
                    },
                    singleLine = true,
                    keyboardOptions = KeyboardOptions.Default.copy(imeAction = ImeAction.Search),
                    keyboardActions = KeyboardActions(
                        onSearch = {
                            onSearch(searchText)
                            keyboardController?.hide()
                            viewModel.searching()
                        }
                    ),
                    modifier = Modifier.weight(1f),
                    textStyle = TextStyle(fontSize = 23.sp, fontWeight = FontWeight.Light),
                    cursorBrush = SolidColor(Color.Black),
                    decorationBox = { innerTextField ->
                        if (isHintDisplayed or searchText.isEmpty()) {
                            Text(text = "Search characters", style = TextStyle(
                                color = Color.Gray,
                                fontSize = 23.sp))
                        }
                        innerTextField()
                    }
                )
                if (searchText.isNotEmpty()) {
                    IconButton(onClick = {
                        searchText = ""
                        onSearch(searchText)
                        keyboardController?.hide()
                        viewModel.searching()
                    }) {
                        Icon(Icons.Filled.Close, contentDescription = "Clear")
                    }
                }
            }
        },
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

@Preview
@Composable
fun SearchScreenPreview() {
    val navController = rememberNavController()
    SearchScreen(navController)
}