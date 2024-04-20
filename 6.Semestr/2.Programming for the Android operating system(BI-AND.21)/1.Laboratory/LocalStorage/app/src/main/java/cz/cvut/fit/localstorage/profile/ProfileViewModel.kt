package cz.cvut.fit.localstorage.profile

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

class ProfileViewModel : ViewModel() {

    private val _screenStateStream = MutableStateFlow(ProfileScreenState())
    val screenStateStream = _screenStateStream.asStateFlow()

    init {
        viewModelScope.launch {
            val name = ProfileDataSource.name
            val darkMode = ProfileDataSource.getDarkModeStream().first()
            _screenStateStream.update { it.copy(name = name, darkMode = darkMode) }
        }
    }

    fun onNameChange(name: String) {
        _screenStateStream.update { it.copy(name = name) }
    }

    fun onDarkModeClick(darkMode: DarkMode) {
        _screenStateStream.update { it.copy(darkMode = darkMode) }
    }

    fun onSaveClick() {
        viewModelScope.launch {
            ProfileDataSource.name = screenStateStream.value.name
            ProfileDataSource.setDarkMode(screenStateStream.value.darkMode)
        }
    }
}

data class ProfileScreenState(
    val name: String = "",
    val darkMode: DarkMode = DarkMode.System,
)
