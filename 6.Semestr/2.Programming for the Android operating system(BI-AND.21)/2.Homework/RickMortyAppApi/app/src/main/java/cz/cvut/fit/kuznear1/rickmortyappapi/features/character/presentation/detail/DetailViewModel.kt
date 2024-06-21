package cz.cvut.fit.kuznear1.rickmortyappapi.features.character.presentation.detail

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.data.CharacterRepository
import cz.cvut.fit.kuznear1.rickmortyappapi.features.character.domain.Character
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

@Suppress("NAME_SHADOWING")
class DetailViewModel(
    private val savedStateHandle: SavedStateHandle,
    private val characterRepository: CharacterRepository
) : ViewModel() {
    private val id: Int
        get() = savedStateHandle.get<Long>(Screens.DetailScreen.ID_KEY)?.toInt() ?: error("Character id is missing")

    private val _screenStateStream = MutableStateFlow(DetailScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            if(id <= 20) {
                val character = characterRepository.getCharacter(id)
                _screenStateStream.update { it.copy(character = character) }
            } else {
                val characterApi = characterRepository.getCharacterApi(id)
                _screenStateStream.update { it.copy(character = characterApi.character) }
            }
        }
    }

    fun onFavouriteClick() {
        viewModelScope.launch {
            val character = characterRepository.getCharacter(id)
            if(character != null) {
                if(character.favourite) {
                    characterRepository.changeCharacterFavourite(id, false)
                    val character = characterRepository.getCharacter(id)
                    _screenStateStream.update { it.copy(character = character) }
                } else {
                    characterRepository.changeCharacterFavourite(id, true)
                    val character = characterRepository.getCharacter(id)
                    _screenStateStream.update { it.copy(character = character) }
                }
            }
        }
    }
}

data class DetailScreenState(
    val character: Character? = null,
)