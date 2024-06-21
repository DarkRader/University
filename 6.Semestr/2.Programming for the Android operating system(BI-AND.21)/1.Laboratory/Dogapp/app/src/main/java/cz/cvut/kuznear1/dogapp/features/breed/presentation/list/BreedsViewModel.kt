package cz.cvut.kuznear1.dogapp.features.breed.presentation.list

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.kuznear1.dogapp.features.breed.domain.BreedsResult
import cz.cvut.kuznear1.dogapp.features.breed.data.BreedRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

class BreedsViewModel(
    private val breedRepository: BreedRepository,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow<BreedsScreenState>(BreedsScreenState.Loading)
    val screenStateStream get() = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val breedsResults = breedRepository.getBreeds()
            _screenStateStream.value = BreedsScreenState.Loaded(breedsResults)
        }
    }
}

sealed interface BreedsScreenState {

    data object Loading : BreedsScreenState

    data class Loaded(val breedsResult: BreedsResult) : BreedsScreenState
}