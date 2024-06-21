package cz.cvut.fit.kuznear1.rickmortyapp

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import cz.cvut.fit.kuznear1.rickmortyapp.model.Character
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch

enum class ScreenState {
    Loading,
    Default,
}
class LoadingViewModel: ViewModel() {
    private val _screenState = MutableStateFlow(ScreenState.Default)
    val screenState: StateFlow<ScreenState> = _screenState

    fun searching() {
        _screenState.value = ScreenState.Loading
        viewModelScope.launch {
            delay(1000)
            _screenState.value = ScreenState.Default
        }
    }

    fun addFavourite(character: Character) {
        _screenState.value = ScreenState.Loading
        viewModelScope.launch {
            delay(1000)
            if(character.favourite == false) {
                character.favourite = true
            } else {
                character.favourite = false
            }
            _screenState.value = ScreenState.Default
        }
    }
}