package cz.cvut.kuznear1.dogapp.features.breed.presentation.list

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Card
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import cz.cvut.kuznear1.dogapp.R
import cz.cvut.kuznear1.dogapp.features.breed.domain.Breed
import cz.cvut.kuznear1.dogapp.features.breed.domain.BreedsResult
import org.koin.androidx.compose.koinViewModel

@Composable
fun BreedsScreen(
    viewModel: BreedsViewModel = koinViewModel(),
    navigateToBreedDetail: (id: String) -> Unit,
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()
    BreedsScreen(screenState, navigateToBreedDetail)
}

@Composable
@OptIn(ExperimentalMaterial3Api::class)
private fun BreedsScreen(
    screenState: BreedsScreenState,
    navigateToBreedDetail: (id: String) -> Unit,
) {
    Scaffold(topBar = {
        TopAppBar(title = { Text(text = stringResource(R.string.bottom_nav_title_breeds)) })
    }) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .fillMaxSize(),
        ) {
            when (screenState) {
                is BreedsScreenState.Loading -> LoadingState()
                is BreedsScreenState.Loaded -> LoadedState(
                    breedsResult = screenState.breedsResult,
                    onBreedClick = { navigateToBreedDetail(it.id) },
                )
            }
        }
    }
}

@Composable
private fun LoadingState() {
    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
        CircularProgressIndicator()
    }
}

@Composable
private fun LoadedState(breedsResult: BreedsResult, onBreedClick: (Breed) -> Unit) {
    Column(Modifier.fillMaxSize()) {
        OutdatedDataBanner(show = !breedsResult.isSuccess)
        Breeds(breeds = breedsResult.breeds, onBreedClick = onBreedClick)
    }
}

@Composable
private fun OutdatedDataBanner(show: Boolean) {
    if (show) {
        Text(
            text = stringResource(R.string.outdated_data_message),
            modifier = Modifier
                .background(color = MaterialTheme.colorScheme.errorContainer)
                .fillMaxWidth()
                .padding(16.dp),
        )
    }
}

@Composable
private fun Breeds(breeds: List<Breed>, onBreedClick: (Breed) -> Unit) {
    LazyColumn(contentPadding = PaddingValues(all = 8.dp)) {
        items(breeds, key = { it.id }) { breed ->
            Card(
                onClick = { onBreedClick(breed) },
                modifier = Modifier
                    .padding(8.dp)
                    .fillMaxWidth()
            ) {
                Text(
                    text = breed.name,
                    style = MaterialTheme.typography.titleLarge.copy(fontSize = 18.sp),
                    modifier = Modifier
                        .padding(16.dp)
                        .fillMaxWidth()
                )
            }
        }
    }
}