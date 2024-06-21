package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.search

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.CharacterRepository
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class SearchViewModel(
    private val characterRepository: CharacterRepository,
) : ViewModel() {

    private val _screenStateStream = MutableStateFlow(SearchScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    fun searchCharacters(query: String) {
        if (query.isBlank()) {
            clearText()
        } else {
            viewModelScope.launch {
                val characters = characterRepository.getFilteredCharacters(query)
                _screenStateStream.update { it.copy(
                    query = query,
                    characters = characters.characters,
                    )
                }
            }
        }
    }

    fun clearText() {
        _screenStateStream.update {
            it.copy(
                query = "",
                characters = emptyList()
            )
        }
    }
}

data class SearchScreenState(
    val query: String = "",
    val characters: List<Character> = emptyList()
)