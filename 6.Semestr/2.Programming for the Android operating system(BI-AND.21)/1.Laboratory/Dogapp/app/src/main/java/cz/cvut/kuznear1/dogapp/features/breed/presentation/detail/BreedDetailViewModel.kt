package cz.cvut.kuznear1.dogapp.features.breed.presentation.detail

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.kuznear1.dogapp.core.presentation.ui.Screens
import cz.cvut.kuznear1.dogapp.features.breed.data.BreedRepository
import cz.cvut.kuznear1.dogapp.features.breed.domain.Breed
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class BreedDetailViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val breedRepository: BreedRepository,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(BreedDetailScreenState())
    val screenStateStream get() = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val breedId: String = savedStateHandle[Screens.BreedDetail.ID] ?: error("Breed id is missing")
            val breed = breedRepository.getBreed(breedId)
            _screenStateStream.update { it.copy(breed = breed) }
        }
    }
}

data class BreedDetailScreenState(val breed: Breed? = null)