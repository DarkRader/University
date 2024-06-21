package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.list

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.CharacterRepository
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class CharactersViewModel(
    private val characterRepository: CharacterRepository,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(CharactersScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val charactersResults = characterRepository.getCharacters()
            _screenStateStream.update { it.copy(characters = charactersResults.characters) }
        }
    }

    fun updateCharacters() {
        viewModelScope.launch {
            val charactersResults = characterRepository.getAllCharacters()
            _screenStateStream.update { it.copy(characters = charactersResults) }
        }
    }
}

data class CharactersScreenState(
    val characters: List<Character> = emptyList()
)