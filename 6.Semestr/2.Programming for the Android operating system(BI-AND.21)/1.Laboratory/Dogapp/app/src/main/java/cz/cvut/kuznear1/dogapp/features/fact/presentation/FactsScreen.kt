package cz.cvut.kuznear1.dogapp.features.fact.presentation

import androidx.compose.foundation.layout.Box
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
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import cz.cvut.kuznear1.dogapp.R
import cz.cvut.kuznear1.dogapp.core.presentation.ui.theme.DogAppTheme
import org.koin.androidx.compose.koinViewModel

@Composable
fun FactsScreen(viewModel: FactsViewModel = koinViewModel()) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()
    FactsScreen(
        screenState,
        onGetFactsClick = { viewModel.onGetFactsClick() },
        onLimitTextChange = { viewModel.onLimitTextChange(it) },
    )
}

@Composable
@OptIn(ExperimentalMaterial3Api::class)
private fun FactsScreen(
    screenState: FactsScreenState,
    onGetFactsClick: () -> Unit,
    onLimitTextChange: (String) -> Unit,
) {
    Scaffold(
        topBar = {
            TopAppBar(title = { Text(text = stringResource(R.string.bottom_nav_title_facts)) })
        }
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .padding(horizontal = 16.dp)
                .fillMaxSize()
        ) {
            val getFactsState = screenState.getFactsState

            Row(Modifier.fillMaxWidth()) {
                Button(
                    enabled = getFactsState !is GetFactsState.Loading,
                    onClick = { onGetFactsClick() },
                ) {
                    Text(text = stringResource(R.string.facts_get_fact_button))
                }
                Spacer(modifier = Modifier.width(16.dp))
                TextField(value = screenState.limit, onValueChange = { onLimitTextChange(it) })
            }

            Spacer(modifier = Modifier.height(16.dp))

            Facts(getFactsState)
        }
    }
}

@Composable
private fun Facts(getFactsState: GetFactsState) {
    when (getFactsState) {
        is GetFactsState.Loading -> FactsLoading()
        is GetFactsState.Error -> FactsError()
        is GetFactsState.Loaded -> FactsLoaded(getFactsState)
    }
}

@Composable
private fun FactsLoading() {
    Box(modifier = Modifier.fillMaxSize()) {
        CircularProgressIndicator(
            modifier = Modifier.align(Alignment.Center),
        )
    }
}

@Composable
private fun FactsLoaded(loadedState: GetFactsState.Loaded) {
    LazyColumn(Modifier.fillMaxSize()) {
        items(loadedState.facts) { fact ->
            Text(text = fact.value, modifier = Modifier.padding(vertical = 8.dp))
        }
    }
}

@Composable
private fun FactsError() {
    Box(modifier = Modifier.fillMaxSize()) {
        Text(
            text = stringResource(R.string.facts_fetch_failed_message),
            modifier = Modifier.align(Alignment.Center),
        )
    }
}

@Preview
@Composable
fun MainScreenPreview() {
    DogAppTheme {
        FactsScreen(FactsScreenState(), {}) {}
    }
}