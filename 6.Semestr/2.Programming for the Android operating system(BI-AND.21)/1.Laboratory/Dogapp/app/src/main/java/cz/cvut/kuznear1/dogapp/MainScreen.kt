package cz.cvut.kuznear1.dogapp

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import cz.cvut.kuznear1.dogapp.ui.theme.DogAppTheme

@Composable
@OptIn(ExperimentalMaterial3Api::class)
fun MainScreen(
    screenState: MainScreenState,
    onGetDogFactsClick: () -> Unit,
    onLimitTextChange: (String) -> Unit,
) {
    Scaffold(topBar = {
        TopAppBar(title = { Text(text = "Networking") })
    }) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .padding(horizontal = 16.dp)
                .fillMaxSize(),
        ) {
            Row(Modifier.fillMaxWidth()) {
                Button(onClick = { onGetDogFactsClick() }) {
                    Text(text = "Get dog facts")
                }
                Spacer(modifier = Modifier.width(16.dp))
                TextField(value = screenState.limit, onValueChange = { onLimitTextChange(it) })
            }
            Spacer(modifier = Modifier.height(16.dp))
            LazyColumn(Modifier.fillMaxSize()) {
                items(screenState.dogFacts) {
                    Text(text = it, modifier = Modifier.padding(vertical = 8.dp))
                }
            }
        }
    }
}

@Preview
@Composable
fun MainScreenPreview() {
    DogAppTheme {
        val screenState = MainScreenState(
            dogFacts = listOf(
                "fact 1",
                "fact 2",
                "fact 3",
            )
        )
        MainScreen(screenState, {}) {}
    }
}