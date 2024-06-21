package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.favorite

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.CharacterRepository
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class FavouriteViewModel(
    private val characterRepository: CharacterRepository,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(FavouriteScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val characters = characterRepository.getAllCharacters()
            val filteredCharacters = characters.filter { it.favourite }
            _screenStateStream.update { it.copy(characters = filteredCharacters) }
        }
    }

    fun updateFavouriteCharacters() {
        viewModelScope.launch {
            val characters = characterRepository.getAllCharacters()
            val filteredCharacters = characters.filter { it.favourite }
            _screenStateStream.update { it.copy(characters = filteredCharacters) }
        }
    }
}

data class FavouriteScreenState(
    val characters: List<Character> = emptyList(),
)